#include "JvmWrapper.hpp"

#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std;

/**
 * Calling Java from C++ with JNI: https://www.codeproject.com/Articles/993067/Calling-Java-from-Cplusplus-with-JNI
 * JNI Method Signature : https://codepedia.tistory.com/entry/JNI-Method-signature
 */

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
		cin.get();
		exit(EXIT_FAILURE);
	}
	cout << "JVM load succeeded: Version ";
	jint ver = env->GetVersion();
	cout << ((ver >> 16) & 0x0F) << "." << (ver & 0x0F) << endl;

	explainableDEVS = env->FindClass("ExplainableDEVS");
	if (explainableDEVS == nullptr) {
		cerr << "ERROR: class not found!" << endl;
		return false;
	}
	cout << "Class found!" << endl;
	jmethodID mid = env->GetStaticMethodID(explainableDEVS, "execute", "()V");
	if (mid == nullptr) {
		cerr << "ERROR: method void execute() not found!" << endl;
		return false;
	}
	env->CallStaticVoidMethod(explainableDEVS, mid);
	cout << endl;
	// TODO: onload..

	mid_tick = env->GetStaticMethodID(explainableDEVS, "tick", "()V");
	if (mid_tick == nullptr) {
		cerr << "ERROR: method void tick() not found!" << endl;
		return false;
	}

	/*
	mid = env->GetStaticMethodID(explainableDEVS, "close", "()V");
	if (mid == nullptr) {
		cerr << "ERROR: method void close() not found!" << endl;
		return false;
	}
	cout << "close" << endl;
	env->CallStaticVoidMethod(explainableDEVS, mid);
	*/
	return true;
}

jobject* JvmWrapper::GetCarByName(std::string name) {
	jclass edevs = env->FindClass("ExplainableDEVS");
	jmethodID mid = env->GetMethodID(edevs, "getCarByName", "(Ljava/lang/String;)Ljava/lang/Object");
	jobject car = env->CallStaticObjectMethod(edevs, mid, name);
	return &car;
}

void JvmWrapper::tick() {
	std::cout << "JVM tick.. " << std::endl;
	if (mid_tick == nullptr || env == nullptr) return;
	env->CallStaticVoidMethod(explainableDEVS, mid_tick);
}

void JvmWrapper::Draw() {

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

void JvmWrapper::Slowdown() {

}

void JvmWrapper::Maintain() {

}