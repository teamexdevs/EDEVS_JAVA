#include "../include/Transducer.hpp"

Transducer::Transducer(std::string EName) : Atomic(EName){
	  SetName(Name);
}

void Transducer::ExtTransitionFN(double E, DevsMessage X){
	 JobID = X.ContentValue();
	 std::cout << "JobID: " << JobID << std::endl;
	 clock += E;

	 Display(Name); Display("(EXT) --> :"); 
	 Display(X.ContentPort());
	 Display(":"); Display(JobID); 
	 Display(" at "); Display(clock);
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
	 Display(Name); Display("(INT) --> "); NewLine();

	 if (Phase == "active") {
	     PrintArrive();
		 PrintSolve();
		 Passivate();
	 }
	 else Continue();
}

void Transducer::OutputFN(void) {
	 Display(Name); Display("(OUT) --> "); NewLine();
	 if (Phase == "active") 
		 MakeContent("out", "NULL");
	 else MakeContent();
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
	 for (int i = 0; i< Arrive.Num; i++){
	     Display("("); Display(Arrive.Jobs[i].ID); 
		 Display(","); Display(Arrive.Jobs[i].Time);
		 Display(") ");
	 }
	 NewLine();
}

void Transducer::PrintSolve(void){
	 NewLine();
     Display("   ---------------------< Solved Jobs >---------------------");
	 NewLine();
	 for (int i = 0; i< Solve.Num; i++){
	     Display("("); Display(Solve.Jobs[i].ID); 
		 Display(","); Display(Solve.Jobs[i].Time);
		 Display(") ");
	 }
	 NewLine();
}