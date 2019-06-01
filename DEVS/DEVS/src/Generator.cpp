#include "../include/Generator.hpp"
#include <iostream>

Generator::Generator() : Atomic() {
	SetName("Generator");
}

Generator::Generator(std::string EName) : Atomic(EName) {
	SetName(EName);
}

void Generator::ExtTransitionFN(double E, DevsMessage X){
	char GeneratorMessage[100]={0,}; 

	Display(Name); Display("(EXT) --> :");
	Display(X.ContentPort()); Display(": ");
	sprintf(GeneratorMessage,"When: %lf",AddTime(GetLastEventTime(),E));
	Display(GeneratorMessage);

	if (X.ContentPort() == "stop") Passivate();
	NewLine();
}

void Generator::IntTransitionFN(void){
	char GeneratorMessage[100]={0,}; 

	Display(Name); Display("(INT) --> ");
	sprintf(GeneratorMessage,"Sigma: %lf  When: %lf",Sigma, AddTime(GetLastEventTime(),Sigma));
	Display(GeneratorMessage);
	if (Phase == "busy") { HoldIn("busy", InterArrivalTime); }
	else { Passivate(); }
	NewLine();
}

void Generator::OutputFN(void){
	std::string O;
	char Num[100]={0,};
	char GeneratorMessage[10000]={0,}; 

	Display(Name); Display("(OUT) --> ");
	std::cout << "GeneratorMessage: " << GeneratorMessage << " >> ";
	sprintf(GeneratorMessage,"Phase: %s  Sigma: %lf  When: %lf", Phase.c_str(), Sigma,GetNextEventTime());
	std::cout << GeneratorMessage << std::endl;
	Display(GeneratorMessage); NewLine();

	if (Phase == "busy") {
		std::cout << "Num: " << Num << " >> ";
		sprintf(Num,"%d",Count++);
		std::cout << Num << std::endl;
		O = "Job-";
		O += Num;
		MakeContent("out", O);
	}
	else MakeContent();
}

void Generator::InitializeFN(void){
	InterArrivalTime = 3;
	Count = 0;

	HoldIn("busy",0.0);
}
