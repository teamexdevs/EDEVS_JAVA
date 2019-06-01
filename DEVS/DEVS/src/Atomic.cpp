#include "../include/Atomic.hpp"

Atomic::Atomic() : Model(){ 
	SetClassName("Atomic");
	ElapsedTime = (double)0.0;
	SetLastEventTime((double)0.0);
	SetNextEventTime(INF);
	Passivate(); 
}

Atomic::Atomic(std::string EName) : Model(EName) { 
	SetClassName("Atomic");
	ElapsedTime = (double)0.0;
	SetLastEventTime((double)0.0);
	SetNextEventTime(INF);
	Passivate(); 
}

Atomic::Atomic(std::string EName, Model *PModel) : Model(EName,PModel) { 
	SetClassName("Atomic");
	ElapsedTime = (double)0.0;
	SetLastEventTime((double)0.0);
	SetNextEventTime(INF);
	Passivate(); 
}

double Atomic::AddSigma(double S) {
	if (Sigma == INF) return INF;
	Sigma += S;
	return Sigma;
}

double Atomic::SubSigma(double S){
	if (Sigma == INF) return INF;
	Sigma -= S;
	return Sigma;
}

double Atomic::AddTime(double T1, double T2) {
	if ((T1 == INF) || (T2 == INF)) return INF;
	return T1 + T2;
}

double Atomic::SubTime(double T1, double T2) {
	if ((T1 == INF) || (T2 == INF)) return INF;
	return T1 - T2;
}

void Atomic::HoldIn(std::string P, double S){
	Phase = P;
	Sigma = S;
}

void Atomic::PassivateIn(std::string P)  { HoldIn(P, INF); }
void Atomic::Passivate(void)        { HoldIn("passive",INF); }
void Atomic::Continue(void)         { HoldIn(Phase,SubTime(Sigma,ElapsedTime)); }

void Atomic::InitialModel(void){
	InitializeFN();
	SetNextEventTime(Sigma);
	if (Parent) Parent->DoneInit((Model *)this,GetNextEventTime());
}

void Atomic::Inject(Model *S, DevsMessage MSG, double Time){ Inject(MSG,Time); }
void Atomic::Inject(DevsMessage MSG){ Inject(MSG,GetNextEventTime());}
void Atomic::Inject(DevsMessage MSG, double Time){
	if ((Time < GetLastEventTime()) || (Time > GetNextEventTime())) return;
	SetInMessage(MSG);
	ElapsedTime = Time - GetLastEventTime();
	ExtTransitionFN(ElapsedTime,MSG);
	SetLastEventTime(Time);
	SetNextEventTime(AddTime(GetLastEventTime(),Sigma));

	if (Parent) Parent->Done((Model *)this,GetNextEventTime());
}

void Atomic::IntTransition(void){ IntTransition(GetNextEventTime()); }
void Atomic::IntTransition(double Time){
	if (Time != GetNextEventTime()) return;
	Output(Time);
	IntTransitionFN();									  
	SetLastEventTime(Time);
	SetNextEventTime(AddTime(GetLastEventTime(),Sigma));
	if (Parent) Parent->Done((Model *)this,GetNextEventTime());
}

void Atomic::MakeContent(void){ return; }
void Atomic::MakeContent(std::string Port, std::string MSG){
	std::string OPort;

	OutMessage.MakeContent(Port,MSG);
	if (Parent) {
		OutMessage.MakeContent(Port,MSG);
		Parent->Inject(this,OutMessage,GetNextEventTime());
	}
	return;
}

void Atomic::Output(void){ Output(GetNextEventTime()); }
void Atomic::Output(double Time){
	double Temp = GetNextEventTime();
	SetNextEventTime(Time);
	OutputFN();
	SetNextEventTime(Temp);
}

void Atomic::Done(Model *P, double Time){ return; }
void Atomic::DoneInit(Model *P, double Time){ return; }