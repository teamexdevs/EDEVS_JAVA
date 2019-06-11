#ifndef __GENERATOR_HPP__
#define __GENERATOR_HPP__

#include "../kernel/include/Tglobal.h"
#include "../kernel/include/Atomic.hpp"

class Generator : public Atomic {
private:
	int     InterArrivalTime;
//	int     ProcessingTime;
//	int     ProblemLevel;
	int     Count;

	int NumberOfCars = 0;
	static const int MaxNumberOfCars = 10;
	static const int LookingSeconds = 100;
	
public:
	Generator();
	Generator(std::string);

    void ExtTransitionFN(double,DevsMessage);
	void IntTransitionFN(void);
	void OutputFN(void);
	void InitializeFN(void);

	int GetNumberOfCars();
	static int GetMaxNumberOfCars();
	static int GetLookingSeconds();
};

#endif	// __GENERATOR_HPP__