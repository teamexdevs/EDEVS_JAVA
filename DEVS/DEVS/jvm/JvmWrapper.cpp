#include "JvmWrapper.hpp"

#include <iostream>
#include <string>
using namespace std;

/**
 * Calling Java from C++ with JNI: https://www.codeproject.com/Articles/993067/Calling-Java-from-Cplusplus-with-JNI
 * JNI Method Signature : https://codepedia.tistory.com/entry/JNI-Method-signature
 */
JvmWrapper::JvmWrapper() {}

JvmWrapper::~JvmWrapper() {
	if (jvm != nullptr) {
		jvm->DestroyJavaVM();
	}
}

void JvmWrapper::init()
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

	jclass jclass = env->FindClass("ExplainableDEVS");
	if (jclass == nullptr) {
		cerr << "ERROR: class not found!" << endl;
	}
	else {
		cout << "Class found!" << endl;
		jmethodID mid = env->GetStaticMethodID(jclass, "execute", "()V");
		//jmethodID mid = env->GetStaticMethodID(jclass, "main", "([Ljava/lang/String)V");
		if (mid == nullptr) {
			cerr << "ERROR: method void main() not found!" << endl;
		}
		else {
			env->CallStaticVoidMethod(jclass, mid);
			cout << endl;
		}
	}
}

void JvmWrapper::Draw() {

}

double JvmWrapper::GetDistance() {
	return 0.0;
}