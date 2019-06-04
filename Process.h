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
	int Line;		//�������� ����
	int Addvelo;	//�߰��Ǵ� �ӵ�
	int Changey;		//��������
public:
	Process(CString);
	Process(char *);

    void ExtTransitionFN(double,DevsMessage);
	void IntTransitionFN(void);
	void OutputFN(void);
	void InitializeFN(void);
	
	void ChangeLine();	//��������
};
