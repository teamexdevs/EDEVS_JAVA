#ifndef __JVM_WRAPPER_HPP__
#define __JVM_WRAPPER_HPP__

#include "jni.h"

class JvmWrapper {
private:
	JavaVM *jvm = nullptr;
	JNIEnv *env = nullptr;
public:
	JvmWrapper();
	~JvmWrapper();
	void init();

	void Draw();
	double GetDistance();
};

#endif	// __JVM_WRAPPER_HPP__