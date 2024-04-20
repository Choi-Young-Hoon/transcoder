#include "transcode/ExecuteList.hpp"
#include "transcode/ExecuteFileUpload.hpp"

ExecuteList::ExecuteList() {
	this->addExecute(ExecuteFileUpload::create());
}

ExecuteList::~ExecuteList() {

}

void ExecuteList::addExecute(ExecuteInterfacePtr request) {
	this->insert(std::make_pair(request->getType(), request));
}

ExecuteInterfacePtr ExecuteList::getExecute(const std::string& type) {
	if (this->find(type) == this->end()) {
		return nullptr;
	}

	return this->at(type);
}