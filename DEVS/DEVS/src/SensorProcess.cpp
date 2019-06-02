#include "../include/SensorProcess.hpp"
#include "../kernel/include/Tglobal.h"

SensorProcess::SensorProcess(std::string entity_name)
	: Atomic(entity_name)
{
	SetClassName("SensorProcess");
}

void SensorProcess::bind(std::string instance_name) {
	/**
	 * TODO: bind DEVS model with Java instance.
	 */
}

void SensorProcess::ExtTransitionFN(double time, DevsMessage message) {
	Display(Name + "(EXT) --> ");
	if (message.ContentPort() == "in") {
		Display("\n[=====================================================================]\n");
		Display("[ TODO: SensorProcess received an external event and check distance.. ]\n");
		int distpx = 31;
		Display("[ distance: " + std::to_string(distpx) + " pixels                                     ]\n");
		MakeContent("out", "distance-" + std::to_string(distpx));
		Display("\\=====================================================================/\n");
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

void SensorProcess::InitializeFN() {
	processing_time = 7.0;
	Passivate();
	ClearMessageQueue(queue);
}