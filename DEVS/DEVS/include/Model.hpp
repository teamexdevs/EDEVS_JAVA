#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "Entity.hpp"
#include "Port.hpp"
#include "Message.hpp"

class Model : public Entity {
public:
	Model *Parent;
	
	PORTS   Ports;
	
	double LastEventTime;
	double NextEventTime;

	DevsMessage InMessage,
	            OutMessage;

public:
    Model();
	Model(std::string);
    
    Model(std::string, Model *);

	void         SetParent(Model *);
	Model      *GetParent(void);

	int          AddCoupling(Model *, Model *, std::string, std::string);

	double       GetLastEventTime(void);
	double       GetNextEventTime(void);

	void         SetLastEventTime(double);
	void         SetNextEventTime(double);

	DevsMessage  GetInMessage(void);
	void         SetInMessage(DevsMessage);
	DevsMessage  GetOutMessage(void);
	void         SetOutMessage(DevsMessage);

    virtual void IntTransition(void)=0;
	virtual void IntTransition(double)=0;
	virtual void Inject(Model *,DevsMessage,double)=0;

	virtual void Inject(DevsMessage,double)=0;
	virtual void Inject(DevsMessage)=0;
	virtual void Output(void)=0;
	virtual void Output(double)=0;

	virtual void InitialModel(void)=0;
	virtual void Done(Model *, double)=0;
	virtual void DoneInit(Model *, double)=0;
};

#endif	// __MODEL_HPP__