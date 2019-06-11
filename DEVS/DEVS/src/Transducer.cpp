#include "../kernel/include/Tglobal.h"

#include "../include/Transducer.hpp"

Transducer::Transducer(std::string EName) : Atomic(EName) {
	SetName(Name);
}

void Transducer::ExtTransitionFN(double E, DevsMessage X) {
	JobID = X.ContentValue();
	Log("JobID: " + JobID);
	NextLine();
	clock += E;

	Log(Name + "(EXT) --> :" + X.ContentPort() + ":" + JobID + " at " + std::to_string(clock));
	NextLine();
	if (Phase == "active"){
	    if (X.ContentPort() == "arriv")       {
	        Arrive.Jobs[Arrive.Num].ID = JobID;
		    Arrive.Jobs[Arrive.Num].Time = clock;
		    Arrive.Num++;
	    }
	    else if (X.ContentPort() == "solved") {
	        Solve.Jobs[Solve.Num].ID = JobID;
		    Solve.Jobs[Solve.Num].Time = clock;
		    Solve.Num++;
	    }
	}
	Continue();
}

void Transducer::IntTransitionFN(void) {
	Log(Name + "(INT) --> ");
	NextLine();

	if (Phase == "active") {
	    PrintArrive();
		PrintSolve();
		Passivate();
	}
	else Continue();
}

void Transducer::OutputFN(void) {
	Log(Name + "(OUT) --> ");
	NextLine();
	if (Phase == "active") 
		MakeContent("out", "NULL");
}

void Transducer::InitializeFN(void){
	clock = (double) 0.0;

	Arrive.Num = 0;
	Solve.Num = 0;

	//HoldIn("active", (double) 100.0);
	HoldIn("active", 1000);
}


void Transducer::PrintArrive(void){
	NextLine();
	Log("   ---------------------< Arrived Jobs >---------------------");
	NextLine();
	for (int i = 0; i < Arrive.Num; i++) {
		Log("(" + Arrive.Jobs[i].ID + "," + std::to_string(Arrive.Jobs[i].Time) + ") ");
	}
	NextLine();
}

void Transducer::PrintSolve(void){
	NextLine();
	Log("   ---------------------< Solved Jobs >---------------------");
	NextLine();
	for (int i = 0; i < Solve.Num; i++) {
		Log("(" + Solve.Jobs[i].ID + "," + std::to_string(Solve.Jobs[i].Time) + ") ");
	}
	NextLine();
}