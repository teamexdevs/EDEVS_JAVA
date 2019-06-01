#include "../include/DriveProcess.hpp"
#include "../include/Tglobal.h"

DriveProcess::DriveProcess(std::string entity_name)
    : Atomic(entity_name)
{
    SetClassName("DriveProcess");
}

void DriveProcess::ExtTransitionFN(double time, DevsMessage message) {
    Display(Name + "(EXT) --> ");
    if (message.ContentPort() == "in") {
        queue.push(message.ContentValue());
        Display(message.ContentPort()); Display(":");
        if (Phase == "busy") {
            Continue();
        } else if (queue.front() != queue.back()) {
            HoldIn("busy", 0.0);
        }
    } else {
        Continue();
    }
    NewLine();
}

void DriveProcess:: IntTransitionFN() {
    Display(Name + "(INT) --> ");
    if (Phase == "busy") {
        if (!queue.empty()) {
            job_id = queue.front();
            Display(" process: " + job_id);
            HoldIn("busy", p_time);
            queue.pop();
        } else {
            Passivate();
        }
    } else {
        Continue();
    }
    NewLine();
}

void DriveProcess::OutputFN() {
    Display(Name + "(OUT) --> ");
    if (Phase == "busy") {
        MakeContent("out", job_id);
    } else {
        MakeContent();
    }
    NewLine();
}

void DriveProcess::InitiailizeFN() {
    p_time = 7.0;
    Passivate();
    ClearMessageQueue(queue);
}