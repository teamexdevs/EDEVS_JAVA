#ifndef __JVM_WRAPPER_HPP__
#define __JVM_WRAPPER_HPP__

#include "jni.h"
#include "../kernel/include/Atomic.hpp"

class JvmWrapper {
private:
	JavaVM *jvm = nullptr;
	JNIEnv *env = nullptr;

	JvmWrapper();
	~JvmWrapper();
public:
	static JvmWrapper& instance() {
		static JvmWrapper* instance = new JvmWrapper();
		return *instance;
	}

	void init();
	void bind(Atomic& model);

	void Draw();
	int GetDistance();
};

#endif	// __JVM_WRAPPER_HPP__