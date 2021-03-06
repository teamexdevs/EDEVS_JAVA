# EDEVS_JAVA

## C++에서 JVM 생성하여 Java 코드 실행하기
1) Visual Studio 2017 프로젝트를 생성합니다.
2) 프로젝트(P) > "프로젝트명" 속성(P) > VC++ 디렉터리 > 포함 디렉터리에 %JDK%/include, %JDK%/include/win32 를 추가합니다.
2-1) 저의 경우 %JDK%는 C:\Program Files\Java\jdk1.8.0_171 입니다.
3) 프로젝트(P) > "프로젝트명" 속성(P) > 링커 > 입력 > 추가 종속성에 %JDK%/lib/jvm.lib 을 추가합니다.
4) jvm.dll을 이용할 수 있도록 시스템 경로(PATH)에 %JDK%/jre/bin/server 를 추가합니다.

## Signature
```
$ javap -s CLASSNAME.class
```

## Architecture
### 2019-06-03
![Architecture_2019-06-03](https://raw.githubusercontent.com/teamexdevs/EDEVS_JAVA/dev/desim/resource/image/arch_20190603.png)

## References
* [Calling Java from C++ with JNI](https://www.codeproject.com/Articles/993067/Calling-Java-from-Cplusplus-with-JNI)
* [JNI Method Signature](https://codepedia.tistory.com/entry/JNI-Method-signature)