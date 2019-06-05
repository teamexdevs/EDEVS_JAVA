#include "../include/ActuatorProcess.hpp"
#include "../kernel/include/Tglobal.h"

ActuatorProcess::ActuatorProcess(std::string entity_name)
	: Atomic(entity_name)
{
	SetClassName("ActuatorProcess");
}

void ActuatorProcess::InitializeFN() {
	processing_time = 7.0;
	Passivate();
	ClearMessageQueue(queue);
}

void ActuatorProcess::ExtTransitionFN(double time, DevsMessage message) {
	Log(Name + "(EXT) --> ");
	if (message.ContentPort() == "accel" || message.ContentPort() == "slowdown" || message.ContentPort() == "maintain") {
		queue.push(message.ContentValue());
		Log(message.ContentPort() + ":" + message.ContentValue());
		if (Phase == message.ContentPort()) {
			Continue();
		}
		else if (queue.front() != queue.back()) {
			HoldIn(message.ContentPort(), 0.0);
		}
	}
	else if (message.ContentPort() == "crossed") {
		HoldIn("crossed", 0.0);
	}
	else {
		Continue();
	}
	NextLine();
}

void ActuatorProcess::IntTransitionFN() {
	Log(Name + "(INT) --> ");
	if (Phase == "accel") {
		if (!queue.empty()) {
			job_id = queue.front();
			SetColor(COLOR_LIGHT_RED);
			Log(" process: " + job_id);
			SetColor(COLOR_DEFAULT);
			HoldIn("busy", processing_time);
			queue.pop();
		}
		else {
			Passivate();
		}
	}
	else if (Phase == "slowdown") {
		if (!queue.empty()) {
			job_id = queue.front();
			SetColor(COLOR_LIGHT_BLUE);
			Log(" process: " + job_id);
			SetColor(COLOR_DEFAULT);
			HoldIn("busy", processing_time);
			queue.pop();
		}
		else {
			Passivate();
		}
	}
	else if (Phase == "maintain") {
		if (!queue.empty()) {
			job_id = queue.front();
			SetColor(COLOR_LIGHT_GREEN);
			Log(" process: " + job_id);
			SetColor(COLOR_DEFAULT);
			HoldIn("busy", processing_time);
			queue.pop();
		}
		else {
			Passivate();
		}
	}
	else if (Phase == "crossed") {
		Passivate();
	}
	else if (Phase == "busy") {
		Passivate();
	}
	else {
		Continue();
	}
	NextLine();
}

void ActuatorProcess::OutputFN() {
	Log(Name + "(OUT) --> ");
	if (Phase == "accel" || Phase == "slowdown" || Phase == "maintain") {
		MakeContent("out", job_id);
	}
	else if (Phase == "crossed") {
		Passivate();
	}
	NextLine();
}