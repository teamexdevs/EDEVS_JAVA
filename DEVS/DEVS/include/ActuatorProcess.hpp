#ifndef __ACTUATOR_PROCESS_HPP__
#define __ACTUATOR_PROCESS_HPP__

#include "../kernel/include/Atomic.hpp"
#include <queue>

class ActuatorProcess : public Atomic {
private:
	std::string job_id;
	double processing_time;
	std::queue<std::string> queue;
public:
	ActuatorProcess(std::string entity_name);

	void InitializeFN(void);
	void ExtTransitionFN(double, DevsMessage);
	void IntTransitionFN(void);
	void OutputFN(void);
};

#endif