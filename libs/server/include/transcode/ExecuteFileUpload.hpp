#pragma once

#include "transcode/ExecuteInterface.hpp"
#include "transcode/Result.hpp"

#include <memory>

class ExecuteFileUpload;
typedef std::shared_ptr<ExecuteFileUpload> ExecuteFileUploadPtr;


class ExecuteFileUpload : public ExecuteInterface {
public:
	static ExecuteFileUploadPtr create();


public:
	explicit ExecuteFileUpload();
	virtual ~ExecuteFileUpload();

public:
	virtual void execute(const json::value& requestJson, Result& result);
};