#ifndef __DRIVE_PROCESS_HPP__
#define __DRIVE_PROCESS_HPP__

#include "Atomic.hpp"
#include <queue>

class DriveProcess : public Atomic {
private:
    std::string job_id;
    double p_time;
    std::queue<std::string> queue;
public:
    DriveProcess(std::string entity_name);

    void ExtTransitionFN(double, DevsMessage);
    void IntTransitionFN(void);
    void OutputFN(void);
    void InitiailizeFN(void);
};

#endif  // __DRIVE_PROCESS_HPP__