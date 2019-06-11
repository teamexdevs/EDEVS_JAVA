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

jobject* JvmWrapper::GetCarByName(std::string name) {
	return nullptr;
	jclass edevs = env->FindClass("ExplainableDEVS");
	jmethodID mid = env->GetMethodID(edevs, "getCarByName", "(Ljava/lang/String;)Ljava/lang/Object");
	jobject car = env->CallStaticObjectMethod(edevs, mid, name);
	return &car;
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
}

void JvmWrapper::tick() {
	Log("JVM tick.. \n");
	Log("_TickID is null: " + std::to_string(_TickID == nullptr) + "\n");
	Log("env is null: " + std::to_string(env == nullptr) + "\n");
	if (_TickID == nullptr || env == nullptr) return;
	env->CallVoidMethod(_ExplainableDEVSInstance, _TickID);
	Log("tock!\n");
}

void JvmWrapper::Execute() {
	env->CallStaticVoidMethod(_ExplainableDEVSClass, _ExecuteID);
}

bool JvmWrapper::GetLaneStatus(int lane) {
	std::cout << "GetLaneStatus[" << lane << "]: " << env->CallBooleanMethod(_ExplainableDEVSInstance, _GetLaneStatusID, lane) << std::endl;
	return env->CallBooleanMethod(_ExplainableDEVSInstance, _GetLaneStatusID, lane) == JNI_TRUE;
}

void JvmWrapper::SpawnCar(std::string name, int lane) {
	env->CallVoidMethod(_ExplainableDEVSInstance, _SpawnCarID, name, lane);

	// TODO: Activate DEVS
}

int JvmWrapper::GetDistance() {
	return rand() % 100;
}

int JvmWrapper::GetVelocity() {
	//return env->CallIntMethod(...);
	return rand() % 10;
}

void JvmWrapper::Accelerate(int speed) {
	//env->CallVoidMethod();
}

void JvmWrapper::Slowdown(int speed) {

}