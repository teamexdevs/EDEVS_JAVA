#include "../include/Tglobal.h"
#include <string>
#include <iostream>

void Display(std::string str) {
	std::cout << "Display(std::string): " << str << std::endl;
}

void NewLine(void) {
	Display("\r\n");
}

void Display(long val){
	printf("Display(long): %ld\n", val);
}

void Display(double val) {
	printf("Display(double): %lf\n", val);
}

void Display(int val) {
	printf("Display(int): %d\n", val);
}

void Display(float val){
	printf("Display(float): %f\n", val);
}