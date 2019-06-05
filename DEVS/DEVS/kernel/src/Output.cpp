#include "../include/Tglobal.h"
#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

void Display(std::string str) {
	std::cout << str;
}

void Display(long val) {
	std::cout << val;
}

void Display(double val) {
	std::cout << val;
}

void Display(int val) {
	std::cout << val;
}

void Display(float val){
	std::cout << val;
}

void NewLine(void) {
	std::cout << std::endl;
}

void SetColor(int color) {
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
#endif
}