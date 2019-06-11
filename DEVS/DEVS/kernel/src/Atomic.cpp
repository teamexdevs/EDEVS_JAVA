#include "../include/Atomic.hpp"

Atomic::Atomic() : Model() {
	SetClassName("Atomic");
	ElapsedTime = (double) 0.0;
	SetLastEventTime((double) 0.0);
	SetNextEventTime(INF);
	Passivate(); 
}

Atomic::Atomic(std::string entity_name) : Model(entity_name) { 
	SetClassName("Atomic");
	ElapsedTime = (double)0.0;
	SetLastEventTime((double)0.0);
	SetNextEventTime(INF);
	Passivate(); 
}

Atomic::Atomic(std::string entity_name, Model *parent) : Model(entity_name, parent) { 
	SetClassName("Atomic");
	ElapsedTime = (double) 0.0;
	SetLastEventTime((double) 0.0);
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

void Atomic::HoldIn(std::string phase, double sigma) {
	Phase = phase;
	Sigma = sigma;
}

void Atomic::PassivateIn(std::string phase) {
	HoldIn(phase, INF);
}

void Atomic::Passivate(void) {
	HoldIn("passive", INF);
}

void Atomic::Continue(void) {
	HoldIn(Phase, SubTime(Sigma, ElapsedTime));
}

void Atomic::InitialModel(void) {
	InitializeFN();
	SetNextEventTime(Sigma);
	if (Parent != nullptr) Parent->DoneInit((Model*) this, GetNextEventTime());
}

void Atomic::Inject(Model *S, DevsMessage message, double time) {
	Inject(message, time);
}

void Atomic::Inject(DevsMessage message) {
	Inject(message, GetNextEventTime());
}

void Atomic::Inject(DevsMessage message, double time) {
	if ((time < GetLastEventTime()) || (time > GetNextEventTime())) return;
	SetInMessage(message);
	ElapsedTime = time - GetLastEventTime();
	ExtTransitionFN(ElapsedTime, message);
	SetLastEventTime(time);
	SetNextEventTime(AddTime(GetLastEventTime(), Sigma));

	if (Parent) Parent->Done((Model* )this, GetNextEventTime());
}

void Atomic::IntTransition(void) {
	IntTransition(GetNextEventTime());
}

void Atomic::IntTransition(double time) {
	if (time != GetNextEventTime()) return;
	Output(time);
	IntTransitionFN();									  
	SetLastEventTime(time);
	SetNextEventTime(AddTime(GetLastEventTime(),Sigma));
	if (Parent != nullptr) Parent->Done((Model*) this, GetNextEventTime());
}

void Atomic::MakeContent(std::string port, std::string message) {
	std::string OPort;
	OutMessage.MakeContent(port, message);
	if (Parent) {
		// FIXME: 메시지를 두 번 보내는 것이 맞는가?
		OutMessage.MakeContent(port, message);
		Parent->Inject(this, OutMessage, GetNextEventTime());
	}
}

void Atomic::Output(void) {
	Output(GetNextEventTime());
}

void Atomic::Output(double time) {
	double temp = GetNextEventTime();
	SetNextEventTime(time);
	OutputFN();
	SetNextEventTime(temp);
}

void Atomic::Done(Model *P, double Time) {
	return;
}

void Atomic::DoneInit(Model *P, double Time) {
	return;
}