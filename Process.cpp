#include "stdafx.h"
#include "process.h"


Process::Process(CString EName) : ATOMIC(EName) {
	SetName(EName);
}

Process::Process(char *EName) : ATOMIC(EName) {
	SetName(EName);
}

void Process::ExtTransitionFN(double Time, DevsMessage MSG)
{
	if (Phase == "busy")
	{
		//가속 감속차선변경 판단
		if (자율차와 비자율차 충돌시간 > 5)
		{
			if (자율차 x위치 - 비자율차 x위치 > 0)
			{
				if (Addvelo < 6)
				{
					Addvelo += 2;
				}
				else
				{
					ChangeLine();
				}
			}

			if (자율차 x위치 - 비자율차 x위치 < 0)
			{
				if (Addvelo > -6)
				{
					Addvelo -= 2;
				}
				else
				{
					ChangeLine();
				}
			}
		}
	}

	if (자율차와 비자율차 충돌시간 < 5)
	{
		ChangeLine();
	}

	else
		Continue();	//그냥주행

}

void Process::IntTransitionFN(void)
{

}

void Process::OutputFN(void) 
{

	if (Phase == "busy")
	{ 
		MakeContent("out",&Why);
	}

	else MakeContent();

}

void Process::InitializeFN(void)
{
	PTime = (double)7.0;
	Passivate();
	Front = Tail = 0;
	Line = 1;
	Addvelo = 0;
	Changey = 0;
}

void Process::ChangeLine()
{
	if (Line == 1)
	{
		if (2번라인이 비어있다면)
		{
			for (int i = 0; i < 5; i++)
			{
				Changey += 500 / 30;
				Line = 2;
			}
		}
	}

	if (Line == 2)
	{
		if (1번라인이 비어있다면)
		{
			for (int i = 0; i < 5; i++)
			{
				Changey -= 500 / 30;
				Line = 1;
			}
		}

		if (3번라인이 비어있다면)
		{
			for (int i = 0; i < 5; i++)
			{
				Changey += 500 / 30;
				Line = 3;
			}
		}
	}

	if (Line == 3)
	{
		if (2번라인이 비어있다면)
		{
			for (int i = 0; i < 5; i++)
			{
				Changey -= 500 / 30;
				Line = 2;
			}
		}
	}

	Addvelo = 0;
}