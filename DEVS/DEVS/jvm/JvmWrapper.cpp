#include "JvmWrapper.hpp"

#include "../kernel/include/Tglobal.h"

#include <string>
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

#if defined(_WIN32)
#elif defined(__linux__)
#elif defined(__APPLE__)
#elif defined(BSD)
#elif defined(__QNX__)
#endif

JvmWrapper::JvmWrapper() {
	srand((unsigned int) time(nullptr));
}

JvmWrapper::~JvmWrapper() {
	if (jvm != nullptr) {
		jvm->DestroyJavaVM();
	}
}

bool JvmWrapper::init()
{
	JavaVMInitArgs vm_args;
	JavaVMOption *options = new JavaVMOption[1];
	options[0].optionString = new char[128] { "-Djava.class.path=." };
	vm_args.version = JNI_VERSION_1_8;
	vm_args.nOptions = 1;
	vm_args.options = options;
	vm_args.ignoreUnrecognized = false;

	jint rc = JNI_CreateJavaVM(&jvm, (void**) &env, &vm_args);
	delete options[0].optionString;
	delete options;
	if (rc != JNI_OK) {
		Log("[JNI_CreateJavaVM] Result code: " + std::to_string(rc) + "\n");
		exit(EXIT_FAILURE);
	}
	Log("JVM load succeeded: Version ");
	jint ver = env->GetVersion();
	Log(std::to_string((ver >> 16) & 0x0F) + "." + std::to_string(ver & 0x0F) + "\n");
	// Explainable DEVS Class
	_ExplainableDEVSClass = env->FindClass("ExplainableDEVS");
	if (_ExplainableDEVSClass == nullptr) {
		Logerr("ERROR: class not found!\n");
		return false;
	}
	Log("Class found!\n");
	// Init Method IDs
	this->InitMethodId();
	// Explainable DEVS Instance
	Log("Call \"static ExplainableDEVS getInstance()\"..\n");
	_ExplainableDEVSInstance = env->CallObjectMethod(_ExplainableDEVSClass, _GetInstanceID);
	this->Execute();

	return true;
}

void JvmWrapper::InitMethodId() {
	Log("Getting method \"static void tick()\"..\n");
	_TickID = env->GetMethodID(_ExplainableDEVSClass, "tick", "()V");
	if (_TickID == nullptr) {
		Logerr("ERROR: method void tick() not found!\n");
	}
	Log("Getting method \"static void execute()\"..\n");
	_ExecuteID = env->GetStaticMethodID(_ExplainableDEVSClass, "execute", "()V");
	if (_ExecuteID == nullptr) {
		Logerr("ERROR: method void execute() not found!\n");
	}
	Log("Getting method \"static ExplainableDEVS getInstance()\"..\n");
	_GetInstanceID = env->GetStaticMethodID(_ExplainableDEVSClass, "getInstance", "()LExplainableDEVS;");
	if (_GetInstanceID == nullptr) {
		Logerr("ERROR: method ExplainableDEVS getInstance() not found!\n");
	}
	Log("Getting method \"boolean getLaneStatus(int lane)\"..\n");
	_GetLaneStatusID = env->GetMethodID(_ExplainableDEVSClass, "getLaneStatus", "(I)Z");
	if (_GetLaneStatusID == nullptr) {
		Logerr("ERROR: method \"boolean getLaneStatus(int lane)\" not found!\n");
	}
	Log("Getting method \"void spawnCar(String name, int lane)\"..\n");
	_SpawnCarID = env->GetMethodID(_ExplainableDEVSClass, "spawnCar", "(Ljava/lang/String;I)V");
	if (_SpawnCarID == nullptr) {
		Logerr("ERROR: method \"void spawnCar(String name, int lane)\" not found!\n");
	}
	Log("Getting method \"SelfDrivingCar getCarByName(String name)\"..\n");
	_GetCarByNameID = env->GetMethodID(_ExplainableDEVSClass, "getCarByName", "(Ljava/lang/String;)LEDEVS/car/SelfDrivingCar;");
	if (_GetCarByNameID == nullptr) {
		Logerr("ERROR: method \"SelfDrivingCar getCarByName(String name)\" not found!\n");
	}
	Log("Getting method \"int getDistance(String name)\"..\n");
	_GetDistanceID = env->GetMethodID(_ExplainableDEVSClass, "getDistance", "(Ljava/lang/String;)I");
	if (_GetDistanceID == nullptr) {
		Logerr("ERROR: method \"int getDistance(String name)\" not found!\n");
	}
	Log("Getting method \"int getVelocityOf(String name)\"..\n");
	_GetVelocityOfID = env->GetMethodID(_ExplainableDEVSClass, "getVelocityOf", "(Ljava/lang/String;)I");
	if (_GetVelocityOfID == nullptr) {
		Logerr("ERROR: method \"int getDistance(String name)\" not found!\n");
	}
	Log("Getting method \"void accelerate(String name)\"..\n");
	_AccelerateID = env->GetMethodID(_ExplainableDEVSClass, "accelerate", "(Ljava/lang/String;I)V");
	if (_AccelerateID == nullptr) {
		Logerr("ERROR: method \"void accelerate(String name)\" not found!\n");
	}
	Log("Getting method \"void slowdown(String name)\"..\n");
	_SlowdownID = env->GetMethodID(_ExplainableDEVSClass, "slowdown", "(Ljava/lang/String;I)V");
	if (_SlowdownID == nullptr) {
		Logerr("ERROR: method \"void slowdown(String name)\" not found!\n");
	}
}

void JvmWrapper::tick() {
	if (_TickID == nullptr || env == nullptr) return;
	env->CallVoidMethod(_ExplainableDEVSInstance, _TickID);
}

void JvmWrapper::Execute() {
	env->CallStaticVoidMethod(_ExplainableDEVSClass, _ExecuteID);
}

bool JvmWrapper::GetLaneStatus(int lane) {
	std::cout << "GetLaneStatus[" << lane << "]: " << env->CallBooleanMethod(_ExplainableDEVSInstance, _GetLaneStatusID, lane) << std::endl;
	return env->CallBooleanMethod(_ExplainableDEVSInstance, _GetLaneStatusID, lane) == JNI_TRUE;
}

void JvmWrapper::SpawnCar(std::string name, int lane) {
	jstring jstr = env->NewStringUTF(name.c_str());
	env->CallVoidMethod(_ExplainableDEVSInstance, _SpawnCarID, jstr, lane);
}

jobject JvmWrapper::GetCarByName(std::string name) {
	jstring jstr = env->NewStringUTF(name.c_str());
	return env->CallObjectMethod(_ExplainableDEVSInstance, _GetCarByNameID, jstr);
}

int JvmWrapper::GetDistance(std::string name) {
	jstring jstr = env->NewStringUTF(name.c_str());
	return env->CallIntMethod(_ExplainableDEVSInstance, _GetDistanceID, jstr);
}

int JvmWrapper::GetVelocityOf(std::string name) {
	jstring jstr = env->NewStringUTF(name.c_str());
	return env->CallIntMethod(_ExplainableDEVSInstance, _GetVelocityOfID, jstr);
}

void JvmWrapper::Accelerate(std::string name, int speed) {
	jstring jstr = env->NewStringUTF(name.c_str());
	env->CallVoidMethod(_ExplainableDEVSInstance, _AccelerateID, jstr, speed);
}

void JvmWrapper::Slowdown(std::string name, int speed) {
	jstring jstr = env->NewStringUTF(name.c_str());
	env->CallVoidMethod(_ExplainableDEVSInstance, _SlowdownID, jstr, speed);
}

bool JvmWrapper::CheckNull(jobject obj) {
	return env->IsSameObject(obj, NULL) == JNI_TRUE;
}