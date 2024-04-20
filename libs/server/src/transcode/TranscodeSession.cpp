#include "transcode/TranscodeSession.hpp"
#include "transcode/Result.hpp"

#include "ByteBuffer.hpp"

#include <iostream>

#include "BoostAsio.hpp"
#include "boost/algorithm/string.hpp"

TranscodeSessionPtr TranscodeSession::create(tcp::socket socket) {
	return std::make_shared<TranscodeSession>(std::move(socket));
}

TranscodeSession::TranscodeSession(tcp::socket socket) 
: socket(std::move(socket)) {

}

TranscodeSession::~TranscodeSession() {

}

void TranscodeSession::start() {
	boost::system::error_code error;
	
	while (true) {
		std::string request;
		if (!this->recvRequest(request)) {
			break;
		}
		std::cout << "request: " << request << std::endl;


		Result result;
		this->execute(request, result);
		int sendSize = this->socket.write_some(asio::buffer(result.serialize()), error);
		if (error) {
			std::cout << "send error: " << error.message() << std::endl;
		}
	}
}

bool TranscodeSession::recvRequest(std::string& requestBody) {

	std::string header;
	if (!this->recvHeader(header)) {
		return false;
	}


	uint64_t bodyLength = 0;
	if (!this->parseHeader(header, bodyLength)) {
		std::cout << "parse failed" << std::endl;
		return false;
	}
	std::cout << "parse Body Length: " << bodyLength << std::endl;


	asio::streambuf recvData;
	boost::system::error_code error;
	if (bodyLength > 0) {
		asio::read(this->socket, recvData, asio::transfer_exactly(bodyLength), error);
		if (error == asio::error::eof) {
			std::cout << "connection closed by peer" << std::endl;
			return false;
		} else if (error) {
			std::cout << "receive error: " << error.message() << std::endl;
			return false;
		}

		requestBody = asio::buffer_cast<const char*>(recvData.data());
	}

	return true;
}

bool TranscodeSession::recvHeader(std::string& header) {
	std::array<char, 1> recvData;

	int crCount = 0;
	int lfCount = 0;
	boost::system::error_code error;

	while (true) {
		this->socket.read_some(asio::buffer(recvData), error);
		if (error == asio::error::eof) {
			std::cout << "connection closed by peer" << std::endl;
			return false;
		} else if (error) {
			std::cout << "receive error: " << error.message() << std::endl;
			return false;
		}

		header += recvData[0];

		if (recvData[0] == '\r') {
			crCount++;
		} else if (recvData[0] == '\n') {
			lfCount++;
		} else {
			crCount = 0;
			lfCount = 0;
		}

		if (crCount == 2 && lfCount == 2) {
			break;
		}
	}
}

bool TranscodeSession::parseHeader(const std::string& header, uint64_t& bodyLegnth) {
	/*
	body_length: 123\r\n 
	위의 내용 파싱
	*/

	std::vector<std::string> lines;
	boost::split(lines, header, boost::is_any_of("\r\n"));
	if (lines.size() < 1) {
		return false;
	}

	// ":" 기준으로 문자열을 나눠 저장한다.
	std::vector<std::string> headerData;
	boost::split(headerData, lines[0], boost::is_any_of(":"));
	if (headerData.size() < 2) { // Header와 Value 값이 있는지 검사
		return false;
	}

	// headerData[1]의 공백과 \r, \n을 전부 제거한다.
	boost::algorithm::trim(headerData[1]);

	bodyLegnth = std::stoull(headerData[1]);

	return true;
}

void TranscodeSession::execute(const std::string& request, Result& result) {
	json::object jsonResponse;

	// Request JSON 파싱
	json::value jsonRequest;
	try {
		jsonRequest = json::parse(request);
	} catch (const boost::system::system_error& e) {
		result.setError("Invalid Json");
		return;
	}

	// Type 체크
	std::string requestType;
	try {
		requestType = jsonRequest.at("type").as_string().c_str();
	} catch (const boost::system::system_error& e) {
		result.setError("Invalid Request");
		return;
	}

	// Request Type 실행
	ExecuteInterfacePtr requestExecute = this->requestExecuteList.getExecute(requestType);
	if (requestExecute == nullptr) {
		result.setError("Invalid Request Type");
		return;
	}

	return requestExecute->execute(jsonRequest, result);
}