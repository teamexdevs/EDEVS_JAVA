#include "../include/Process.hpp"
#include <string>

Process::Process(std::string entity_name) : Atomic(entity_name) { 
    SetName(entity_name); 
}

void Process::ExtTransitionFN(double Time, DevsMessage MSG) {
	Log(Name + "(EXT) --> ");
	if (MSG.ContentPort() == "in") {

		// Put job into the Queue
		if(Tail < 50)
		{
			try {
				Queue[Tail++] = MSG.ContentValue();
				Log(MSG.ContentPort() + ":" + JobID);
			}
			catch (std::length_error e) {
				std::cerr << e.what() << std::endl;
			}
		}
		
		if (Phase == "busy"){
			Continue();
		}
		else
		{
			if(Front != Tail)
				HoldIn("busy",0.0);
		}
	}
	else Continue();
	NextLine();
}

void Process::IntTransitionFN(void) {
	Log(Name + "(INT) --> ");
	if (Phase == "busy"){
		// Get job from the Queue
		if(Front != Tail)
		{
			// processing
			JobID = Queue[Front++];
			Log(" process : " + JobID);
			HoldIn("busy",PTime);
		}
		else
			Passivate();
	}
	else Continue();
	NextLine();
}

void Process::OutputFN(void) {
	Log(Name + "(OUT) --> ");
	
	if (Phase == "busy"){ 
		MakeContent("out", JobID);
	}
	NextLine();
}

void Process::InitializeFN(void){
	PTime = (double)7.0;
	Passivate();
	Front = Tail = 0;
}