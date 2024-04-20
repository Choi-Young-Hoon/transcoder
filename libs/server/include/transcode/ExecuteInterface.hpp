#pragma once

#include "transcode/Result.hpp"

#include <string>
#include <memory>

#include "BoostAsio.hpp"

class ExecuteInterface;
typedef std::shared_ptr<ExecuteInterface> ExecuteInterfacePtr;


class ExecuteInterface {
public:
	explicit ExecuteInterface(const std::string& type);
	virtual ~ExecuteInterface();

public:
	std::string getType();

	virtual void execute(const json::value& requestJson, Result& result) = 0;

private:
	std::string type;
};