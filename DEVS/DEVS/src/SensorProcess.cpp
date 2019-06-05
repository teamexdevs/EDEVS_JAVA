#include "../include/SensorProcess.hpp"
#include "../kernel/include/Tglobal.h"

#include <cmath>
#include <ctime>

SensorProcess::SensorProcess(std::string entity_name)
	: Atomic(entity_name)
{
	SetClassName("SensorProcess");
}

void SensorProcess::InitializeFN() {
	srand((unsigned int) time(NULL));
	processing_time = 1.0;
	Passivate();
	ClearMessageQueue(queue);
}

void SensorProcess::bind(std::string instance_name) {
	/**
	 * TODO: bind DEVS model with Java instance.
	 */
}

void SensorProcess::ExtTransitionFN(double time, DevsMessage message) {
	Display(Name + "(EXT) --> ");
	if (message.ContentPort() == "in") {
		queue.push(message.ContentValue());
		Display(message.ContentPort() + ":" + message.ContentValue());
		if (Phase == "busy") {
			Continue();
		}
		else if (queue.front() != queue.back()) {
			HoldIn("busy", 0.0);
		}
	}
	else {
		Continue();
	}
	NewLine();
}

void SensorProcess::IntTransitionFN() {
	Display(Name + "(INT) --> ");
	if (Phase == "busy") {
		if (!queue.empty()) {
			job_id = queue.front();
			Display(" process: " + job_id);
			HoldIn("busy", processing_time);
			/**
			 * TODO [0]: 주행이 완료되었는지 확인한다.
			 */
			/**
			 * TODO [1]: Java-binded Car 객체로부터 앞차와의 거리값을 읽어온다.
			 */
			int distance_in_pixel = rand() % 100;
			Display(" (distance: " + std::to_string(distance_in_pixel) + " meters) ");
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
	NewLine();
}

void SensorProcess::OutputFN() {
	Display(Name + "(OUT) --> ");
	if (Phase == "busy") {
		MakeContent("out", job_id);
	}
	NewLine();
}