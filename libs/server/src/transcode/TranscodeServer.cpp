#include "transcode/TranscodeServer.hpp"
#include "transcode/TranscodeSession.hpp"

#include <iostream>

TranscodeServer::TranscodeServer(short port)
: acceptor(ioContext, tcp::endpoint(tcp::v4(), port)) {

}

TranscodeServer::~TranscodeServer() {

}


bool TranscodeServer::start() {
	this->asyncAccept();

	try {
		this->ioContext.run();
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

void TranscodeServer::stop() {
	this->ioContext.stop();
}

void TranscodeServer::asyncAccept() {
	this->acceptor.async_accept([this](boost::system::error_code error, tcp::socket socket) {
		if (!error) {
			TranscodeSessionPtr session = TranscodeSession::create(std::move(socket));
			session->start();
		}

		this->asyncAccept();
	});
}