#include "../include/transd.hpp"

Transd::Transd(std::string EName) : Atomic(EName){
	  SetName(Name);
}

void Transd::ExtTransitionFN(double E, DevsMessage X){
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

void Transd::IntTransitionFN(void) {
	 Display(Name); Display("(INT) --> "); NewLine();

	 if (Phase == "active") {
	     PrintArrive();
		 PrintSolve();
		 Passivate();
	 }
	 else Continue();
}

void Transd::OutputFN(void) {
	 Display(Name); Display("(OUT) --> "); NewLine();
	 if (Phase == "active") 
		 MakeContent("out", "NULL");
	 else MakeContent();
}

void Transd::InitializeFN(void){
	  clock = (double)0.0;

	  Arrive.Num = 0;
	  Solve.Num = 0;

	  HoldIn("active",(double)100.0);
}


void Transd::PrintArrive(void){
	 NewLine();
     Display("   ---------------------< Arrived Jobs >---------------------");
	 NewLine();
	 for (int i=0; i<Arrive.Num; i++){
	     Display("("); Display(Arrive.Jobs[i].ID); 
		 Display(","); Display(Arrive.Jobs[i].Time);
		 Display(") ");
	 }
	 NewLine();
}

void Transd::PrintSolve(void){
	 NewLine();
     Display("   ---------------------< Solved Jobs >---------------------");
	 NewLine();
	 for (int i=0; i<Solve.Num; i++){
	     Display("("); Display(Solve.Jobs[i].ID); 
		 Display(","); Display(Solve.Jobs[i].Time);
		 Display(") ");
	 }
	 NewLine();
}