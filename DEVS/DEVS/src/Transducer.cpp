#include "../kernel/include/Tglobal.h"

#include "../include/Transducer.hpp"

Transducer::Transducer(std::string EName) : Atomic(EName) {
	SetName(Name);
}

void Transducer::ExtTransitionFN(double E, DevsMessage X) {
	JobID = X.ContentValue();
	Display("JobID: " + JobID);
	NewLine();
	clock += E;

	Display(Name + "(EXT) --> :" + X.ContentPort() + ":" + JobID + " at " + std::to_string(clock));
	NewLine();
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
	 Display(Name + "(INT) --> ");
	 NewLine();

	 if (Phase == "active") {
	     PrintArrive();
		 PrintSolve();
		 Passivate();
	 }
	 else Continue();
}

void Transducer::OutputFN(void) {
	 Display(Name + "(OUT) --> ");
	 NewLine();
	 if (Phase == "active") 
		 MakeContent("out", "NULL");
}

void Transducer::InitializeFN(void){
	  clock = (double)0.0;

	  Arrive.Num = 0;
	  Solve.Num = 0;

	  HoldIn("active",(double)100.0);
}


void Transducer::PrintArrive(void){
	 NewLine();
     Display("   ---------------------< Arrived Jobs >---------------------");
	 NewLine();
	 for (int i = 0; i < Arrive.Num; i++) {
	     Display("(" + Arrive.Jobs[i].ID + "," + std::to_string(Arrive.Jobs[i].Time) + ") ");
	 }
	 NewLine();
}

void Transducer::PrintSolve(void){
	 NewLine();
     Display("   ---------------------< Solved Jobs >---------------------");
	 NewLine();
	 for (int i = 0; i < Solve.Num; i++) {
	     Display("(" + Solve.Jobs[i].ID + "," + std::to_string(Solve.Jobs[i].Time) + ") ");
	 }
	 NewLine();
}