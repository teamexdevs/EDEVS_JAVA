#ifndef __TRANSD_HPP__
#define __TRANSD_HPP__

#include "Tglobal.h"
#include "Atomic.hpp"

typedef struct {
    std::string ID;
	double  Time;
} JOB;

typedef struct {
    JOB Jobs[100];
	int Num;
} JOBS;

class Transd : public Atomic {
public:
    std::string JobID;
	double  clock;
    JOBS    Arrive, Solve;

public:
	Transd(std::string);

    void ExtTransitionFN(double,DevsMessage);
	void IntTransitionFN(void);
	void OutputFN(void);
	void InitializeFN(void);

	void PrintArrive(void);
	void PrintSolve(void);
};

#endif	// __TRANSD_HPP__