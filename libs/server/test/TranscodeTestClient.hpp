#pragma once

#include "BoostAsio.hpp"

#include <string>
#include <memory>

class TranscodeTestClient {
public:
	explicit TranscodeTestClient(const std::string& ip, const unsigned short port)
	: serverIp(ip)
	, serverPort(port)
	, socket(ioContext) {}

	virtual ~TranscodeTestClient() {}


public:
	bool connect() {
		asio::ip::tcp::resolver resolver(this->ioContext);
		auto endpoints = resolver.resolve(this->serverIp, std::to_string(this->serverPort));

		boost::system::error_code error;
		this->endpoint = boost::asio::connect(this->socket, endpoints, error);
		if (error) {
			std::cout << error.what() << std::endl;
			return false;
		}

		return true;
	}

	bool request(const json::object& request, boost::json::value& response) {
		std::string requestStr = json::serialize(request);
		
		/*
		body_length: {requestStr.size()}\r\n
		\r\n
		{requestStr}

		위의 형식으로 서버에 전송
		*/
		std::string requestData;
		requestData += "body_length: " + std::to_string(requestStr.size()) + "\r\n";
		requestData += "\r\n";
		requestData += requestStr;


		boost::system::error_code error;
		this->socket.write_some(asio::buffer(requestData), error);
		if (error) {
			return false;
		}
		
		char responseData[4096] = { 0, };
		this->socket.read_some(asio::buffer(responseData), error);
		if (error) {
			return false;
		}

		//response = json::parse(responseData);
		response = boost::json::parse(responseData);

		return true;
	}


private:
	std::string    serverIp;
	unsigned short serverPort;

	asio::io_context ioContext;
	asio::ip::tcp::endpoint endpoint;
	asio::ip::tcp::socket   socket;
};