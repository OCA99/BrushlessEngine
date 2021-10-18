#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* gameObject)
{
	this->gameObject = gameObject;
}