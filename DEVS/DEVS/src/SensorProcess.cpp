#include "../include/SensorProcess.hpp"
#include "../kernel/include/Tglobal.h"

#include "../jvm/JvmWrapper.hpp"

#include <cmath>

SensorProcess::SensorProcess(std::string entity_name, int id)
	: Atomic(entity_name)
{
	SetClassName("SensorProcess");
	this->id = id;
}

void SensorProcess::InitializeFN() {
	processing_time = 3.0;
	Passivate();
}

/**
 * ONLY ONCE!
 */
void SensorProcess::ExtTransitionFN(double time, DevsMessage message) {
	SetColor(COLOR_LIGHT_RED);
	Log(Name + "(EXT) --> ");

	if (message.ContentPort() == "in") {
		Log(message.ContentPort() + ":" + message.ContentValue() + "\n");
		HoldIn("busy", processing_time);	// passive -> busy
	}
	SetColor(COLOR_DEFAULT);
	/*
	if (message.ContentPort() == "in") {
		queue.push(message.ContentValue());
		Log(message.ContentPort() + ":" + message.ContentValue());
		if (Phase == "busy") {	// busy == sensing
			Continue();
		}
		else if (queue.front() != queue.back()) {
			HoldIn("busy", 0.0);
		}
	}
	else {
		Continue();
	}
	NextLine();
	*/
}

/**
 * Infinite Loop
 */
void SensorProcess::IntTransitionFN() {
	SetColor(COLOR_LIGHT_PURPLE);
	Log(Name + "(INT) --> ");
	if (Phase == "busy") {

		HoldIn("busy", processing_time);
		// TODO [0]: 주행이 완료되었는지 확인한다.
		std::string car_id = "Car#" + std::to_string(id);
		jobject car = JvmWrapper::GetInstance().GetCarByName(car_id);
		if (JvmWrapper::GetInstance().CheckNull(car)) {
			Log("[SensorProcess] " + car_id + " :: Car is gone..\n");
			MakeContent("passed", job_id);
			Passivate();
			SetColor(COLOR_DEFAULT);
			return;
		}
		int distance = JvmWrapper::GetInstance().GetDistance(car_id);
		Log("[SensorProcess] " + car_id + " :: distance: " + std::to_string(distance) + "\n");
		if (distance <= 300) {
			Log("[SensorProcess] slowdown " + car_id + " speed 1..\n");
			JvmWrapper::GetInstance().Slowdown(car_id, 1);
			Log("[SensorProcess] " + car_id + " has decelerated..\n");
		}
		/*
		if (!queue.empty()) {
			job_id = queue.front();
			Log(" process: " + job_id);
			HoldIn("busy", processing_time);
			// TODO [0]: 주행이 완료되었는지 확인한다.
			// TODO [1]: Java-binded Car 객체로부터 앞차와의 거리값을 읽어온다.
			int distance_in_pixel = JvmWrapper::GetInstance().GetDistance();
			SetColor(COLOR_LIGHT_BLUE);
			Log(" (distance: " + std::to_string(distance_in_pixel) + " meters) ");
			SetColor(COLOR_DEFAULT);
			// TODO [2]: 현재 속력을 고려했을 때 일정 거리 이하일 경우 대처를 취한다.
			queue.pop();
		}
		else {
			Passivate();
		}
		*/
	}
	else {
		Continue();
	}
	NextLine();
	SetColor(COLOR_DEFAULT);
}

void SensorProcess::OutputFN() {
	Log(Name + "(OUT) --> ");
	if (Phase == "busy") {
		MakeContent("out", job_id);
	}
	NextLine();
}