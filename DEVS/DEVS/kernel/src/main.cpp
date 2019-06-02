#include "../include/Tglobal.h"
#include "../include/Entstr.hpp"

#include "../../include/Generator.hpp"
#include "../../include/Transducer.hpp"
#include "../../include/Process.hpp"
#include "../../include/SensorProcess.hpp"

#include "../../jvm/JvmWrapper.hpp"

#include <thread>

void jvm_on_thread() {
	Display(" ============ JVM ================ \n");
	JvmWrapper *jvm = new JvmWrapper();
	jvm->init();
}

int main()
{
	// Jvm
	std::thread t = std::thread(jvm_on_thread);
	
	// DEVS
	Display(" ============ DEVS ================ \n");
	EntStr *efp = new EntStr("ef-p");

	SensorProcess *sensorProcess = new SensorProcess("SensorProcess");
	efp->AddItem(sensorProcess);
	efp->AddItem(new Digraph("ef"));

	efp->AddCouple("ef", "SensorProcess", "OUT", "in");
	efp->AddCouple("SensorProcess", "ef", "out", "IN");

	efp->SetCurrentItem("ef");
	efp->AddItem(new Generator("genr"));
	efp->AddItem(new Transducer("transd"));
	efp->AddCouple("ef", "transd", "IN", "solved");
	efp->AddCouple("transd", "genr", "out", "stop");

	efp->AddCouple("genr", "ef", "out", "OUT");            
	efp->AddCouple("genr", "transd", "out", "arriv");

	efp->Restart();

	t.join();

	return 0;
}