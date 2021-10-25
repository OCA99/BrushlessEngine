#include "Transform.h"
#include "Application.h"

Transform::Transform(Application* app, GameObject* gameObject) : Component(app, gameObject) {
	this->position.Set(0, 0, 0);
	this->rotation.Set(0, 0, 0);
	this->scale.Set(0, 0, 0);
}