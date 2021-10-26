#include "Transform.h"
#include "Application.h"

Transform::Transform(Application* app, GameObject* gameObject) : Component(app, gameObject) {
	this->transform = IdentityMatrix;
}