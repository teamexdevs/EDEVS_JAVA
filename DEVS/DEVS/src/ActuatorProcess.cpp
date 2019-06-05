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

void ActuatorProcess::IntTransitionFN() {
	Display(Name + "(INT) --> ");
	if (Phase == "busy") {
		if (!queue.empty()) {
			job_id = queue.front();
			SetColor(COLOR_RED);
			Display(" process: " + job_id);
			SetColor(COLOR_DEFAULT);
			HoldIn("busy", processing_time);
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

void ActuatorProcess::OutputFN() {
	Display(Name + "(OUT) --> ");
	if (Phase == "busy") {
		MakeContent("out", job_id);
	}
	NewLine();
}