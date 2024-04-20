#pragma once

#include "transcode/ExecuteList.hpp"

#include "BoostAsio.hpp"
#include "ByteBuffer.hpp"

#include <memory>

class TranscodeSession;
typedef std::shared_ptr<TranscodeSession> TranscodeSessionPtr;

class TranscodeSession {
public:
	static TranscodeSessionPtr create(tcp::socket socket);


public:
	explicit TranscodeSession(tcp::socket socket);
	virtual ~TranscodeSession();


public:
	void start();


private:
	bool recvRequest(std::string& requestBody);
	bool recvHeader (std::string& header);
	bool parseHeader(const std::string& header, uint64_t& bodyLength);

	void execute(const std::string& request, Result& result);


private:
	tcp::socket socket;

	ExecuteList requestExecuteList;
};