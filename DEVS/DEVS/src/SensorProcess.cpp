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
	ClearMessageQueue(queue);
}

/**
 * ONLY ONCE!
 */
void SensorProcess::ExtTransitionFN(double time, DevsMessage message) {
	SetColor(COLOR_LIGHT_RED);
	Log(Name + "(EXT) --> ");

	Log(message.ContentPort() + ":" + message.ContentValue() + "\n");
	SetColor(COLOR_DEFAULT);
	HoldIn("busy", processing_time);
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
	Log(Name + "(INT) --> ");
	if (Phase == "busy") {

		HoldIn("busy", processing_time);
		// TODO [0]: ������ �Ϸ�Ǿ����� Ȯ���Ѵ�.
		jobject car = JvmWrapper::GetInstance().GetCarByName("Car#" + id);
		if (JvmWrapper::GetInstance().CheckNull(car)) {
			SetColor(COLOR_BRIGHT_WHITE);
			Log("[SensorProcess] " + GetName() + " :: Car is gone..\n");
			SetColor(COLOR_DEFAULT);
		}

		/*
		if (!queue.empty()) {
			job_id = queue.front();
			Log(" process: " + job_id);
			HoldIn("busy", processing_time);
			// TODO [0]: ������ �Ϸ�Ǿ����� Ȯ���Ѵ�.
			// TODO [1]: Java-binded Car ��ü�κ��� �������� �Ÿ����� �о�´�.
			int distance_in_pixel = JvmWrapper::GetInstance().GetDistance();
			SetColor(COLOR_LIGHT_BLUE);
			Log(" (distance: " + std::to_string(distance_in_pixel) + " meters) ");
			SetColor(COLOR_DEFAULT);
			// TODO [2]: ���� �ӷ��� ������� �� ���� �Ÿ� ������ ��� ��ó�� ���Ѵ�.
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