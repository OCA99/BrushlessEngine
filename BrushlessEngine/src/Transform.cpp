#include "Transform.h"

Transform::Transform(GameObject* gameObject) : Component(gameObject) {
	this->position.Set(0, 0, 0);
	this->rotation.Set(0, 0, 0);
	this->scale.Set(0, 0, 0);
}