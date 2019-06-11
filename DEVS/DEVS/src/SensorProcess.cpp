#include "../include/SensorProcess.hpp"
#include "../kernel/include/Tglobal.h"

#include "../jvm/JvmWrapper.hpp"

#include <cmath>

SensorProcess::SensorProcess(std::string entity_name)
	: Atomic(entity_name)
{
	SetClassName("SensorProcess");
}

void SensorProcess::InitializeFN() {
	processing_time = 3.0;
	Passivate();
	ClearMessageQueue(queue);
}

void SensorProcess::ExtTransitionFN(double time, DevsMessage message) {
	Log(Name + "(EXT) --> ");
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
}

void SensorProcess::IntTransitionFN() {
	Log(Name + "(INT) --> ");
	if (Phase == "busy") {
		if (!queue.empty()) {
			job_id = queue.front();
			Log(" process: " + job_id);
			HoldIn("busy", processing_time);
			/**
			 * TODO [0]: 주행이 완료되었는지 확인한다.
			 */
			/**
			 * TODO [1]: Java-binded Car 객체로부터 앞차와의 거리값을 읽어온다.
			 */
			int distance_in_pixel = JvmWrapper::instance().GetDistance();
			SetColor(COLOR_LIGHT_BLUE);
			Log(" (distance: " + std::to_string(distance_in_pixel) + " meters) ");
			SetColor(COLOR_DEFAULT);
			/**
			 * TODO [2]: 현재 속력을 고려했을 때 일정 거리 이하일 경우 대처를 취한다.
			 */
			queue.pop();
		}
		else {
			Passivate();
		}
	}
	else {
		Continue();
	}
	NextLine();
}

void SensorProcess::OutputFN() {
	Log(Name + "(OUT) --> ");
	if (Phase == "busy") {
		if (rand() % 100 < 30) {
			MakeContent("crossed", job_id);
			Passivate();
			return;
		}
		MakeContent("out", job_id);
	}
	NextLine();
}