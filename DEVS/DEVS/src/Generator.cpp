#include "../include/Generator.hpp"

#include "../jvm/JvmWrapper.hpp"

Generator::Generator() : Atomic() {
	SetName("Generator");
}

Generator::Generator(std::string entity_name) : Atomic(entity_name) {
	SetName(entity_name);
}

void Generator::ExtTransitionFN(double E, DevsMessage X) {
	Log(Name + "(EXT) --> :" + X.ContentPort() + ": When: " + std::to_string(AddTime(GetLastEventTime(), E)));
	if (X.ContentPort() == "stop") Passivate();
	NextLine();
}

void Generator::IntTransitionFN(void) {
	Log(Name + "(INT) --> Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(AddTime(GetLastEventTime(), Sigma)));
	if (Phase == "busy") { HoldIn("busy", InterArrivalTime); }
	else { Passivate(); }
	NextLine();
}

void Generator::OutputFN(void) {
	Log(Name + "(OUT) --> Phase: " + Phase.c_str() + " / Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(GetNextEventTime()));
	NextLine();

	if (Phase == "busy") {
		// TODO: 메시지 내용
		// TODO: 새로운 자동차 추가
		bool laneStatus = JvmWrapper::GetInstance().GetLaneStatus(1);

		MakeContent("out", "Job-" + std::to_string(Count++));
	}
}

void Generator::InitializeFN(void) {
	InterArrivalTime = 3;
	Count = 0;

	HoldIn("busy", 0.0);
}
