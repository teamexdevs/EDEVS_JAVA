#ifndef __BINDABLE_MODEL_HPP__
#define __BINDABLE_MODEL_HPP__

#include "../kernel/include/Digraph.hpp"

#ifdef _WIN32
#include "jni.h"
#endif

class BindableModel : public Digraph {
private:
#ifdef _WIN32
	jobject *binded;
#endif
public:
	BindableModel(std::string);
	~BindableModel();

	void bind(std::string);
};

#endif	// __BINDABLE_MODEL_HPP__