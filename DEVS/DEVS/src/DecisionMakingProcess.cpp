#include "../include/DecisionMakingProcess.hpp"
#include "../kernel/include/Tglobal.h"

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

void DecisionMakingProcess::IntTransitionFN() {
	Display(Name + "(INT) --> ");
	if (Phase == "busy") {
		if (!queue.empty()) {
			job_id = queue.front();
			Display(" process: " + job_id);
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

void DecisionMakingProcess::OutputFN() {
	Display(Name + "(OUT) --> ");
	if (Phase == "busy") {
		MakeContent("out", job_id);
	}
	NewLine();
}