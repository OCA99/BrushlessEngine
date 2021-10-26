#include "Transform.h"

Transform::Transform(GameObject* gameObject) : Component(gameObject) {
	this->transform = IdentityMatrix;
}