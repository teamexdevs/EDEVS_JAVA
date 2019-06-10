#include "../include/DecisionMakingProcess.hpp"
#include "../kernel/include/Tglobal.h"

#include <cmath>

DecisionMakingProcess::DecisionMakingProcess(std::string entity_name)
	: Atomic(entity_name)
{
	SetClassName("DecisionMakingProcess");
}

void DecisionMakingProcess::InitializeFN() {
	processing_time = 7.0;
	Passivate();
	ClearMessageQueue(queue);
}

void DecisionMakingProcess::ExtTransitionFN(double time, DevsMessage message) {
	Log(Name + "(EXT) --> ");
	if (message.ContentPort() == "in") {
		queue.push(message.ContentValue());
		Log(message.ContentPort() + ":" + message.ContentValue());
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
	NextLine(2);
}

void DecisionMakingProcess::IntTransitionFN() {
	Log(Name + "(INT) --> ");
	if (Phase == "busy") {
		if (!queue.empty()) {
			job_id = queue.front();
			Log(" process: " + job_id);
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
	NextLine();
}

void DecisionMakingProcess::OutputFN() {
	Log(Name + "(OUT) --> ");
	if (Phase == "busy") {
		switch (rand() % 3) {
		case 0:
			MakeContent("accel", job_id);
			break;
		case 1:
			MakeContent("slowdown", job_id);
			break;
		//case 2:
		//	MakeContent("maintain", job_id);
		default:
			break;
		}
	}
	NextLine();
}