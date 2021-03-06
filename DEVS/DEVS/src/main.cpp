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
void GenerateNewCar();

static EntStr *efp = nullptr;

int main()
{
	// Jvm
	//std::thread t = std::thread(init_jvm);
	init_jvm();

	// DEVS
	Log(" ============ DEVS ================ \n");
	efp = new EntStr("ef-p");

	// ========================== PRE-DEFINE and PASSIVATE =============================
	Log("Generating car processes..\n");
	SetColor(COLOR_AQUA);
	for (int i = 1; i <= Generator::GetMaxNumberOfCars(); ++i) {
		std::string bid = "SelfDriveProcess#" + std::to_string(i);
		//BindableModel *selfDriveProcess = new BindableModel(bid);
		Digraph *selfDriveProcess = new Digraph(bid);
		efp->AddItem(selfDriveProcess);
		efp->SetCurrentItem(bid);
		std::string sid = "SensorProcess#" + std::to_string(i);
		SensorProcess *sensorProcess = new SensorProcess(sid, i);
		efp->AddItem(sensorProcess);
		efp->AddCouple(bid, sid, "in", "in");
		std::string did = "DecisionMakingProcess#" + std::to_string(i);
		DecisionMakingProcess *decisionMakingProcess = new DecisionMakingProcess(did);
		efp->AddItem(decisionMakingProcess);
		efp->AddCouple(sid, did, "out", "in");
		std::string aid = "ActuatorProcess#" + std::to_string(i);
		ActuatorProcess *actuatorProcess = new ActuatorProcess(aid, i);
		efp->AddItem(actuatorProcess);
		efp->AddCouple(did, aid, "accel", "accel");
		efp->AddCouple(did, aid, "slowdown", "slowdown");
		// Reactive Passivate (on external event)
		efp->AddCouple(sid, did, "passed", "passed");
		efp->AddCouple(did, aid, "passed", "passed");
		efp->AddCouple(aid, bid, "passed", "passed");
		Log(bid + " has generated!\n");
	}
	SetColor(COLOR_DEFAULT);
	Log("Successfully generated!\n");
	// =================================================================================

	efp->SetCurrentItem("ef-p");

	efp->AddItem(new Digraph("ef"));
	//efp->AddCouple("ef", "SelfDriveProcess#1", "OUT", "in");
	//efp->AddCouple("SelfDriveProcess#1", "ef", "out", "IN");
	for (int i = 1; i <= Generator::GetMaxNumberOfCars(); ++i) {
		std::string id = std::to_string(i);
		efp->AddCouple("ef", "SelfDriveProcess#" + id, "OUT-" + id, "in");
		efp->AddCouple("SelfDriveProcess#" + id, "ef", "out", "IN-" + id);
	}

	efp->SetCurrentItem("ef");
	efp->AddItem(new Generator("genr"));
	efp->AddItem(new Transducer("transd"));
	efp->AddCouple("ef", "transd", "IN", "solved");
	efp->AddCouple("transd", "genr", "out", "stop");

	//efp->AddCouple("genr", "ef", "out", "OUT");
	//efp->AddCouple("genr", "transd", "out", "arriv");
	for (int i = 1; i <= Generator::GetMaxNumberOfCars(); ++i) {
		std::string id = std::to_string(i);
		efp->AddCouple("genr", "ef", "out-" + id, "OUT-" + id);
		efp->AddCouple("genr", "transd", "out-" + id, "arriv");
	}

	efp->Restart();

	//t.join();

	Log("Press any key to continue.. ");
	std::getchar();

	return 0;
}

void init_jvm() {
	Log(" ============ JVM ================ \n");
	static JvmWrapper& jvm = JvmWrapper::GetInstance();
	jvm.init();
}