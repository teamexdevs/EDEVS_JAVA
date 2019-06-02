#ifndef __DIGRAPH_HPP__
#define __DIGRAPH_HPP__

#include "Coupled.hpp"
#include "Message.hpp"

class Digraph : public Coupled {
public:
	ListElement *P;
public:
	Digraph(std::string);

	void IntTransition(double);
	void IntTransition(void);
	void Inject(Model *, DevsMessage,double);
	void Inject(DevsMessage);
    void Inject(DevsMessage,double);

	void InitialModel(void);
	void Done(Model *, double);
	void DoneInit(Model *, double);

	double GetMinTime(void);
};

#endif	// __DIGRAPH_HPP__