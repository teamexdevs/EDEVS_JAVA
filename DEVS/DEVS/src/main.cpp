#include "../kernel/include/Tglobal.h"
#include "../kernel/include/Entstr.hpp"

#include "../include/Generator.hpp"
#include "../include/Transducer.hpp"
#include "../include/SensorProcess.hpp"
#include "../include/DecisionMakingProcess.hpp"
#include "../include/ActuatorProcess.hpp"
#include "../include/BindableModel.hpp"

#include "../jvm/JvmWrapper.hpp"

#include <thread>

void init_jvm();

int main()
{
	// Jvm
	//std::thread t = std::thread(init_jvm);
	init_jvm();

	// DEVS
	Log(" ============ DEVS ================ \n");
	EntStr *efp = new EntStr("ef-p");

	// =================================================================================
	BindableModel *selfDriveProcess = new BindableModel("SelfDriveProcess");
	//Digraph *selfDriveProcess = new Digraph("SelfDriveProcess");
	efp->AddItem(selfDriveProcess);
	efp->SetCurrentItem("SelfDriveProcess");

	SensorProcess *sensorProcess = new SensorProcess("SensorProcess");
	efp->AddItem(sensorProcess);
	efp->AddCouple("SelfDriveProcess", "SensorProcess", "in", "in");

	DecisionMakingProcess *decisionMakingProcess = new DecisionMakingProcess("DecisionMakingProcess");
	efp->AddItem(decisionMakingProcess);
	efp->AddCouple("SensorProcess", "DecisionMakingProcess", "out", "in");

	ActuatorProcess *actuatorProcess = new ActuatorProcess("ActuatorProcess");
	efp->AddItem(actuatorProcess);
	efp->AddCouple("DecisionMakingProcess", "ActuatorProcess", "accel", "accel");
	efp->AddCouple("DecisionMakingProcess", "ActuatorProcess", "slowdown", "slowdown");
	efp->AddCouple("DecisionMakingProcess", "ActuatorProcess", "maintain", "maintain");
	efp->AddCouple("SensorProcess", "ActuatorProcess", "crossed", "crossed");
	efp->AddCouple("ActuatorProcess", "SelfDriveProcess", "out", "out");

	efp->SetCurrentItem("ef-p");
	// =================================================================================

	efp->AddItem(new Digraph("ef"));
	efp->AddCouple("ef", "SelfDriveProcess", "OUT", "in");
	efp->AddCouple("SelfDriveProcess", "ef", "out", "IN");

	efp->SetCurrentItem("ef");
	efp->AddItem(new Generator("genr"));
	efp->AddItem(new Transducer("transd"));
	efp->AddCouple("ef", "transd", "IN", "solved");
	efp->AddCouple("transd", "genr", "out", "stop");

	efp->AddCouple("genr", "ef", "out", "OUT");            
	efp->AddCouple("genr", "transd", "out", "arriv");

	efp->Restart();

	//t.join();

	

	return 0;
}

void init_jvm() {
	Log(" ============ JVM ================ \n");
	static JvmWrapper& jvm = JvmWrapper::instance();
	jvm.init();
}