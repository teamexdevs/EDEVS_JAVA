#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <iostream>

class Entity {
public:	
	std::string ClassName;
	std::string Name;
	int			GettableChildren;

public:
    Entity(std::string);
	Entity();

	void SetClassName(std::string);
	void SetName(std::string);
	
	std::string GetClassName(void);
	std::string GetName(void);
};

#endif	// __ENTITY_HPP__