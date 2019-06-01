#include "../include/Tglobal.h"
#include "../include/Entstr.hpp"

#include "../include/Generator.hpp"
#include "../include/Transd.hpp"
#include "../include/Process.hpp"

int main()
{
	EntStr *efp = new EntStr("ef-p");
	efp->AddItem(new Process("Process"));
	efp->AddItem(new Digraph("ef"));

	efp->AddCouple("ef", "Process", "OUT", "in");
	efp->AddCouple("Process","ef", "out", "IN");           

	efp->SetCurrentItem("ef");
	efp->AddItem(new Generator("genr"));
	efp->AddItem(new Transd("transd"));
	efp->AddCouple("ef", "transd", "IN", "solved");
	efp->AddCouple("transd", "genr", "out", "stop");

	efp->AddCouple("genr", "ef", "out", "OUT");            
	efp->AddCouple("genr", "transd", "out", "arriv");

	efp->Restart();

	return 0;
}