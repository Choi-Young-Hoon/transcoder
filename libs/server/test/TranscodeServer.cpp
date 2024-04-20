#include "gtest/gtest.h"

#include "transcode/TranscodeServer.hpp"

#include "TranscodeTestClient.hpp"

#include <iostream>
#include <memory>

class TranscodeServerTest : public ::testing::Test {
protected:
	static void SetUpTestCase() {
		server = std::make_shared<TranscodeServer>(10000);
		std::thread([&]() {
			server->start();
		}).detach();
	}

	static void TearDownTestCase() {
		server->stop();
	}


private:
	static std::shared_ptr<TranscodeServer> server;
};
std::shared_ptr<TranscodeServer> TranscodeServerTest::server = nullptr;


TEST_F(TranscodeServerTest, FILE_UPLOAD_VALID) {
	TranscodeTestClient client("192.168.219.103", 10000);
	ASSERT_EQ(client.connect(), true);

	json::object request;
	request["type"] = "upload";
	request["fileSize"] = 100;
	request["fileName"] = "test.txt";

	boost::json::value response;
	ASSERT_EQ(client.request(request, response), true);

	std::cout << "response: " << response << std::endl;
	ASSERT_EQ(response.at("result").as_string(), "success");
}


TEST_F(TranscodeServerTest, FILE_UPLOAD_INVALID) {
	TranscodeTestClient client("127.0.0.1", 10000);
	ASSERT_EQ(client.connect(), true);

	json::object request;
	request["type"] = "upload";
	request["fileSize_1"] = 100;
	request["fileName_1"] = "test.txt";

	boost::json::value response;
	ASSERT_EQ(client.request(request, response), true);

	std::cout << "response: " << response << std::endl;
	ASSERT_TRUE(response.at("result").as_string() != "success");
}


TEST_F(TranscodeServerTest, BAD_REQUEST_TYPE) {
	TranscodeTestClient client("127.0.0.1", 10000);
	ASSERT_EQ(client.connect(), true);

	json::object request;
	request["type"] = "sdgfagadsgfsdfsdafasdfs2345321562356";

	boost::json::value response;
	ASSERT_EQ(client.request(request, response), true);

	std::cout << "response: " << response << std::endl;
	ASSERT_TRUE(response.at("result").as_string() != "success");
}