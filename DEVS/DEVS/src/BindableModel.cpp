#include "../include/BindableModel.hpp"

#include "../jvm/JvmWrapper.hpp"

BindableModel::BindableModel(std::string entity_name)
	: Digraph(entity_name)
{
	SetClassName("BindableModel");
	binded = nullptr;
}

BindableModel::~BindableModel() {}

void BindableModel::bind(std::string instance_name) {
#ifdef _WIN32
	this->binded = JvmWrapper::instance().GetCarByName(instance_name);
#endif
}