#pragma once

#include "boost/json.hpp"

#include <string>

class Result {
public:
	explicit Result();
	virtual ~Result();

	
public:
	std::string serialize();


public:
	void setSuccess();
	void setError(const std::string& error);
	void setJson(const std::string& key, const std::string& value);
	void setJson(const std::string& key, int value);


private:
	boost::json::object jsonObject;
};