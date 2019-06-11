#include "../include/Digraph.hpp"

Digraph::Digraph(std::string EName)
	: Coupled(EName)
{
	SetClassName("Digraph");
}

void Digraph::IntTransition(double Time){
	if (Time != GetNextEventTime()) return;

	SetLastEventTime(Time);

	P = Children.FindFirstList(Time);
	if (P == nullptr) return;

	do {
		P->Model->IntTransition(Time);
		P = Children.FindNextList(Time);
		if (P == nullptr) break;
	} while (true);
}

/* --------------- Body of Inject Function in Atomic model --------------------
     if ((Time < GetLastEventTime()) || (Time > GetNextEventTime())) return;
	 SetInMessage(MSG);
	 ElapsedTime = Time - GetLastEventTime();
	 ExtTransitionFN(ElapsedTime,MSG);
	 SetLastEventTime(Time);
	 SetNextEventTime(AddTime(GetLastEventTime(),Sigma));

	 if (Parent) Parent->Done((Model *)this,GetNextEventTime());
*/

void Digraph::Inject(Model *From, DevsMessage MSG, double Time) {
	 PortPair *PPair, *Temp;
	 std::string  PPort;

	 if ((From == this) && (Parent)) Parent->Inject(this,MSG,Time);

	 PPort = MSG.ContentPort();
	 PPair = Ports.FindFirstPair(PPort);
	 Temp = Ports.Curr;

	 do {
	 	if (PPair == nullptr) break;

		OutMessage.MakeContent(PPair->ToPort,MSG.ContentValue());
		if ((PPair->FromModel == From) || (From == Parent))
		   ((Model *)(PPair->ToModel))->Inject(this,OutMessage,Time);
		Ports.Curr = Temp;
		PPair = Ports.FindNextPair(PPort);
		Temp = Ports.Curr;
	 } while (true);
}

void Digraph::InitialModel(void){
	 Children.AllInitial();
	 if (Parent) Parent->DoneInit(this,GetMinTime());
	 SetNextEventTime(GetMinTime());
}

void Digraph::Done(Model *M, double T){ 
     Children.SetOne(M,T); 
	 SetNextEventTime(GetMinTime());
	 if (Parent) Parent->Done(this,GetMinTime());
}

void Digraph::DoneInit(Model *M, double T){ 
     Children.SetOne(M,T); 
}

double Digraph::GetMinTime(void){ return Children.GetMinTime(); }

void Digraph::IntTransition(void) {}
void Digraph::Inject(DevsMessage MSG) {
	 Inject(this,MSG,GetNextEventTime());
}

void Digraph::Inject(DevsMessage MSG, double T) {
	 Inject(this,MSG,T);
}