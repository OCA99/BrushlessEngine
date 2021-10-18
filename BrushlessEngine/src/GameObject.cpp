#include "GameObject.h"

GameObject::GameObject(std::string name, bool active = true) {
	this->name = name;
	this->active = active;
}