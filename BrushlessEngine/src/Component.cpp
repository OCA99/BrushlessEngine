#include "Component.h"
#include "GameObject.h"

#include "Application.h"

Component::Component(Application* app, GameObject* gameObject, COMPONENT_TYPE type)
{
	this->app = app;
	this->gameObject = gameObject;
	this->type = type;
}