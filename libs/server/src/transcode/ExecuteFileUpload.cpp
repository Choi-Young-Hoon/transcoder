#include "transcode/ExecuteFileUpload.hpp"

#include <iostream>


ExecuteFileUploadPtr ExecuteFileUpload::create() {
	return std::make_shared<ExecuteFileUpload>();
}


ExecuteFileUpload::ExecuteFileUpload()
: ExecuteInterface("upload") {

}

ExecuteFileUpload::~ExecuteFileUpload() {

}

void ExecuteFileUpload::execute(const json::value& requestJson, Result& result) {
	int64_t		fileSize = 0;
	std::string fileName;
	try {
		fileSize = requestJson.at("fileSize").as_int64();
		fileName = requestJson.at("fileName").as_string().c_str();
	} catch (const std::exception& e) {
		std::cout << __FUNCTION__ << e.what() << "  - parse error" << std::endl;
		result.setError("Invalid Request");
		return;
	}
	
	std::cout << "file size: " << fileSize << " file name: " << fileName << std::endl;
	
	result.setSuccess();
}