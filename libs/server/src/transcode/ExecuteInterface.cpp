#include "transcode/ExecuteInterface.hpp"

ExecuteInterface::ExecuteInterface(const std::string& type)
: type(type) {

}

ExecuteInterface::~ExecuteInterface() {

}

std::string ExecuteInterface::getType() {
	return type;
}