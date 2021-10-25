#include "Component.h"
#include "GameObject.h"

#include "Application.h"

Component::Component(Application* app, GameObject* gameObject)
{
	this->app = app;
	this->gameObject = gameObject;
}