#ifndef __JVM_WRAPPER_HPP__
#define __JVM_WRAPPER_HPP__

#include "jni.h"

#include <vector>

class JvmWrapper {
private:
	JavaVM *jvm = nullptr;
	JNIEnv *env = nullptr;

	std::vector<jobject> cars;

	jclass explainableDEVS;
	jmethodID mid_tick;

	JvmWrapper();
	~JvmWrapper();
public:
	static JvmWrapper& instance() {
		static JvmWrapper* instance = new JvmWrapper();
		return *instance;
	}

	bool init();
	void tick();

	jobject* GetCarByName(std::string);
	void Draw();
	int GetDistance();
	int GetVelocity();
	void Accelerate(int speed);
	void Slowdown();
	void Maintain();
};

#endif	// __JVM_WRAPPER_HPP__