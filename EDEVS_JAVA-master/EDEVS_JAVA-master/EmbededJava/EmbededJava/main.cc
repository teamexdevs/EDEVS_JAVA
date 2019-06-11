#include "jni.h"
#include <iostream>
using namespace std;

/**
 * Calling Java from C++ with JNI: https://www.codeproject.com/Articles/993067/Calling-Java-from-Cplusplus-with-JNI
 * JNI Method Signature : https://codepedia.tistory.com/entry/JNI-Method-signature
 */
int main()
{
	JavaVM *jvm = nullptr;
	JNIEnv *env = nullptr;

	JavaVMInitArgs vm_args;
	JavaVMOption *options = new JavaVMOption[1];
	options[0].optionString = new char[100] { "-Djava.class.path=." };
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

	jclass jclass = env->FindClass("Gui");
	if (jclass == nullptr) {
		cerr << "ERROR: class not found!" << endl;
	}
	else {
		cout << "Class Main found!" << endl;
		jmethodID mid = env->GetStaticMethodID(jclass, "test", "()V");
		//jmethodID mid = env->GetStaticMethodID(jclass, "main", "([Ljava/lang/String;)V");
		if (mid == nullptr) {
			cerr << "ERROR: method void main() not found!" << endl;
		}
		else {
			env->CallStaticVoidMethod(jclass, mid);
			cout << endl;
		}
	}

	jvm->DestroyJavaVM();
	cin.get();

	return 0;
}