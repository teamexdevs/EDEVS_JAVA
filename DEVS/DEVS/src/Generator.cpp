#include "../include/Generator.hpp"

Generator::Generator() : Atomic() {
	SetName("Generator");
}

Generator::Generator(std::string EName) : Atomic(EName) {
	SetName(EName);
}

void Generator::ExtTransitionFN(double E, DevsMessage X){
	Display(Name + "(EXT) --> :" + X.ContentPort() + ": When: " + std::to_string(AddTime(GetLastEventTime(), E)));
	if (X.ContentPort() == "stop") Passivate();
	NewLine();
}

void Generator::IntTransitionFN(void) {
	Display(Name + "(INT) --> Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(AddTime(GetLastEventTime(), Sigma)));
	if (Phase == "busy") { HoldIn("busy", InterArrivalTime); }
	else { Passivate(); }
	NewLine();
}

void Generator::OutputFN(void){
	Display(Name + "(OUT) --> Phase: " + Phase.c_str() + " / Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(GetNextEventTime()));
	NewLine();

	if (Phase == "busy") {
		MakeContent("out", "Job-" + std::to_string(Count++));
	}
	else MakeContent();
}

void Generator::InitializeFN(void){
	InterArrivalTime = 3;
	Count = 0;

	HoldIn("busy",0.0);
}
