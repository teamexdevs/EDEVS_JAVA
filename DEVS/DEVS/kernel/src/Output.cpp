#include "../include/Tglobal.h"
#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

void Log(std::string str) {
	std::cout << str;
}

void NextLine(int lines) {
	while (lines--)
		std::cout << std::endl;
}

void SetColor(Color color) {
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
#endif
}