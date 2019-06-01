#include "../include/Entity.hpp"

Entity::Entity(std::string entity_name) {
	SetClassName("Entity");
	SetName(entity_name); 
	GettableChildren = 0;
}

Entity::Entity()
	: Entity::Entity("") { }

void Entity::SetClassName(std::string CName){
	ClassName = CName;
}

void Entity::SetName(std::string EName){
	Name = EName;
}

std::string Entity::GetClassName(void){
	return ClassName;
}

std::string Entity::GetName(void){
	return Name;
}