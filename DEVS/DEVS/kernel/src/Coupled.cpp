#include "../include/Coupled.hpp"

Coupled::Coupled(std::string entity_name) : Model(entity_name) {
	GettableChildren = 1;
}

void Coupled::AddChild(Model *M){ Children.AddOne(M); }
void Coupled::AddChild(Model *M, double T) { Children.AddOne(M,T); }
int  Coupled::IsDevsChild(Model *M) { return Children.IsIn(M); }
int  Coupled::NumOfChild(void)   { return Children.GetLength(); }