#pragma once

#include "ExecuteInterface.hpp"

#include <unordered_map>
#include <memory>

class ExecuteList : public std::unordered_map<std::string, ExecuteInterfacePtr> {
public:
	explicit ExecuteList();
	virtual ~ExecuteList();


public:
	void addExecute(ExecuteInterfacePtr execute);


public:
	ExecuteInterfacePtr getExecute(const std::string& type);
};