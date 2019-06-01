#include "../include/Model.hpp"

Model::Model()
	: Model::Model("") { }

Model::Model(std::string entity_name)
	: Model::Model(entity_name, nullptr) { }

Model::Model(std::string entity_name, Model *parent_model) {
	SetClassName("Model");
	SetName(entity_name);
	Parent = parent_model;
}

int Model::AddCoupling(Model *FModel, Model *TModel, std::string FPort, std::string TPort){
	return Ports.AddCoupling((Entity *)FModel,(Entity *)TModel,FPort,TPort);
}

double Model::GetLastEventTime(void){
	return LastEventTime;
}

double Model::GetNextEventTime(void){
	return NextEventTime;
}

void   Model::SetLastEventTime(double LTime){
	LastEventTime = LTime;
}

void   Model::SetNextEventTime(double NTime){
	NextEventTime = NTime;
}


DevsMessage Model::GetInMessage(void){
	return InMessage;
}

void   Model::SetInMessage(DevsMessage MSG){
	InMessage = MSG;
}

DevsMessage Model::GetOutMessage(void){
	return OutMessage;
}

void   Model::SetOutMessage(DevsMessage MSG){
	OutMessage = MSG;
}

void    Model::SetParent(Model *P){ Parent = P; }
Model *Model::GetParent(void) { return Parent; }
