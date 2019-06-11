#ifndef __JVM_WRAPPER_HPP__
#define __JVM_WRAPPER_HPP__

#include "jni.h"

#include <vector>

class JvmWrapper {
private:
	JavaVM *jvm = nullptr;
	JNIEnv *env = nullptr;

	std::vector<jobject> cars;

	jclass _ExplainableDEVSClass;
	jobject _ExplainableDEVSInstance;
	jmethodID _TickID;
	jmethodID _ExecuteID;
	jmethodID _GetInstanceID;
	jmethodID _GetLaneStatusID;
	jmethodID _SpawnCarID;
	jmethodID _GetCarByNameID;

	JvmWrapper();
	~JvmWrapper();
public:
	static JvmWrapper& GetInstance() {
		static JvmWrapper* instance = new JvmWrapper();
		return *instance;
	}

	bool init();

	void InitMethodId();
	void tick();
	void Execute();
	bool GetLaneStatus(int lane);
	void SpawnCar(std::string name, int lane);
	jobject GetCarByName(std::string);

	int GetDistance();
	int GetVelocity();
	void Accelerate(int speed);
	void Slowdown(int speed);

	// Utility
	bool CheckNull(jobject);
};

#endif	// __JVM_WRAPPER_HPP__