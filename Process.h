#pragma once
#include "stdafx.h"
#include "Tglobal.h"
#include "atomic.h"

class Process : public ATOMIC {
public:
    CString JobID;
	double PTime;
    CString Queue[50];
    int Front,Tail;
	int Line;		//무인차의 차선
	int Addvelo;	//추가되는 속도
	int Changey;		//차선변경
public:
	Process(CString);
	Process(char *);

    void ExtTransitionFN(double,DevsMessage);
	void IntTransitionFN(void);
	void OutputFN(void);
	void InitializeFN(void);
	
	void ChangeLine();	//차선변경
};
