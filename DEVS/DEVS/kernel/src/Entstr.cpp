#include "../include/Entstr.hpp"
#include "../../kernel/include/Tglobal.h"

#ifdef _WIN32
#include "../../jvm/JvmWrapper.hpp"
#endif

EntStr::EntStr(std::string EName) : Digraph(EName) {
	SetClassName("EntStr");
	SetName(EName);
	ChildList.AddModel(EName,this);
	CurrentItem = this;
	SetClock((double)0.0);
	LimitClock = INF;
	CClock = 0.0;
}

void EntStr::SetLimit(double T){
	LimitClock = T;
}

double EntStr::SetClock(double T){
	Clock = T;
	return T;
}

double EntStr::GetClock(void){ return Clock; }

double EntStr::AddClock(double T){
	if ((Clock == INF) || (T == INF)) return SetClock(INF);
	Clock += T;
	if (Clock < 0) return SetClock(INF);
	return GetClock();
}

int  EntStr::SCI(Model *Curr){ return SetCurrentItem(Curr); }
int  EntStr::SetCurrentItem(Model *Curr){
	CurrentItem = Curr;
	return 1;
}

int  EntStr::SetCurrentItem(std::string Curr){
	Model *p;
	p = ChildList.GetModel(Curr);
	if (p == nullptr) return 0;
	CurrentItem = p;
	return 1;
}

int  EntStr::AddItem(Model *M) {
	if (M == nullptr) {
		std::cerr << "Null pointer assigned!" << std::endl;
		return 0;
	}
	if (CurrentItem == this) {
		if (((EntStr *)CurrentItem)->IsDevsChild(M)) return 0;
		((EntStr *)CurrentItem)->AddChild(M);
	}
	else {
		if (((Coupled *)CurrentItem)->IsDevsChild(M)) return 0;
		((Coupled *)CurrentItem)->AddChild(M);
	}
	ChildList.AddModel(M->GetName(), M);
	M->SetParent(CurrentItem);
	return 1;
}

int  EntStr::AddCouple(Model *FModel, Model *TModel, std::string FPort, std::string TPort){
	CurrentItem->AddCoupling(FModel, TModel, FPort, TPort);
	return 1;
}

int  EntStr::AddCouple(std::string FModel, std::string TModel, std::string FPort, std::string TPort){
	Model *F, *T;

	F = ChildList.GetModel(FModel);
	T = ChildList.GetModel(TModel);

	if ((F == nullptr) || (T == nullptr)) return 0;

	AddCouple(F,T,FPort,TPort);
	return 1;
}

void EntStr::Initialize(void){ 
	Children.AllInitial(); 
	Clock = 0.0;
}

void EntStr::Restart(void) {
	Log("[" + GetClassName() + "] Restart!\n");
	double Time;
	ListElement *P;

	Initialize();
	//Clock = (double)0.0;

	do {
		StepStart();
		Time = Children.GetMinTime();
		SetClock(Time); 
		if (Time == INF) break;
		if (Time > LimitClock) break;
		P = Children.FindFirstList(Time);
		if (P == nullptr) break;
	} while (true);
}

void EntStr::StepStart(void) {
	Log("[" + GetClassName() + "] StepStart!\n");
	double Time, TTime;
	ListElement *P;

	CClock = Children.GetMinTime();
	TTime = CClock;

	do {
		Time = Children.GetMinTime();
		if (CClock != Time) break;
		SetClock(Time); 
		if (Time == INF) break;
		if (Time > LimitClock) break;
		P = Children.FindFirstList(Time);
		if (P == nullptr) break;
		P->Model->IntTransition(Time);
	} while (true);

#ifdef _WIN32
	//JvmWrapper::instance().tick();
#endif

	Log("One step ended...");
	OutputFN(TTime);
}


void EntStr::IntTransition(double T){ return; }

void EntStr::Inject(std::string P, std::string V){
	OutMessage.MakeContent(P,V);
	Digraph::Inject(OutMessage,(double)0.0);
}

void EntStr::DoneInit(Model *M, double T){ Children.SetOne(M,T); }
void EntStr::Done(Model *M, double T)    { Children.SetOne(M,T); }

void EntStr::IntTransition(void) {}
void EntStr::Output(double T) {}
void EntStr::Output(void) {}
void EntStr::InitialModel(void) {}

void EntStr::OutputFN(double clk) {
	Log("Global Clock (Root): " + std::to_string(clk));
	NextLine(2);
}