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
		//���� ������������ �Ǵ�
		if (�������� �������� �浹�ð� > 5)
		{
			if (������ x��ġ - �������� x��ġ > 0)
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

			if (������ x��ġ - �������� x��ġ < 0)
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

	if (�������� �������� �浹�ð� < 5)
	{
		ChangeLine();
	}

	else
		Continue();	//�׳�����

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
		if (2�������� ����ִٸ�)
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
		if (1�������� ����ִٸ�)
		{
			for (int i = 0; i < 5; i++)
			{
				Changey -= 500 / 30;
				Line = 1;
			}
		}

		if (3�������� ����ִٸ�)
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
		if (2�������� ����ִٸ�)
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