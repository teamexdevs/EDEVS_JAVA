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
	if (Phase == "busy") {
		HoldIn("busy", InterArrivalTime);
	} else {
		Passivate();
	}
	NextLine();
}

void Generator::OutputFN(void) {
	Log(Name + "(OUT) --> Phase: " + Phase.c_str() + " / Sigma: " + std::to_string(Sigma) + " / When: " + std::to_string(GetNextEventTime()));
	NextLine();

	if (Phase == "busy") {
		// TODO: 메시지 내용
		// TODO: 새로운 자동차 추가
		for (int lane = 1; lane <= 3; ++lane) {
			bool laneStatus = JvmWrapper::GetInstance().GetLaneStatus(lane);
			if (laneStatus == true) {
				SetColor(COLOR_AQUA);
				Log("[Generator] Lane #" + std::to_string(lane) + " is empty.\n");
				std::string car_id = "Car#" + std::to_string(++NumberOfCars);
				JvmWrapper::GetInstance().SpawnCar(car_id, lane);
				Log("[Generator] " + car_id + " has spawned.\n");
				SetColor(COLOR_DEFAULT);

				// Activate Model #i
				std::string out = "out-" + std::to_string(NumberOfCars);
				std::string job = "job-" + std::to_string(Count++);
				Log("[Generator] out: " + out + ", job: " + job + "\n");
				MakeContent(out, job);
				//MakeContent("out-" + std::to_string(NumberOfCars), "Job-" + std::to_string(Count++));
			}
			else {
				Log("[Generator] Lane #" + std::to_string(lane) + " is not empty.\n");
			}
		}
		Log("[Generator_OutputFN] Lane finished.\n");

		//MakeContent("out", "Job-" + std::to_string(Count++));
	}
}

void Generator::InitializeFN(void) {
	InterArrivalTime = 1;
	Count = 0;

	HoldIn("busy", 0.0);
}

int Generator::GetNumberOfCars() {
	return NumberOfCars;
}

int Generator::GetMaxNumberOfCars() {
	return MaxNumberOfCars;
}

int Generator::GetLookingSeconds() {
	return LookingSeconds;
}