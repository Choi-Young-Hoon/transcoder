#pragma once

#include "BoostAsio.hpp"


class TranscodeServer {
public:
	explicit TranscodeServer(short port);
	virtual ~TranscodeServer();


public:
	bool start();
	void stop();


private:
	void asyncAccept();


private:
	boost::asio::io_context ioContext;
	tcp::acceptor acceptor;
};