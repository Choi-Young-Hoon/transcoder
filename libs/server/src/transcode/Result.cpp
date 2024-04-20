#include "transcode/Result.hpp"

Result::Result() {

}

Result::~Result() {

}

std::string Result::serialize() {
	return boost::json::serialize(this->jsonObject);
}

void Result::setSuccess() {
	this->jsonObject["result"] = "success";
}

void Result::setError(const std::string& error) {
	this->jsonObject["result"] = "error";
	this->jsonObject["error"] = error;
}

void Result::setJson(const std::string& key, const std::string& value) {
	this->jsonObject[key] = value;
}

void Result::setJson(const std::string& key, int value) {
	this->jsonObject[key] = value;
}

