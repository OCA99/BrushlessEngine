#include "Transform.h"
#include "Application.h"

Transform::Transform(Application* app, GameObject* gameObject) : Component(gameObject) {
	this->transform = IdentityMatrix;
}