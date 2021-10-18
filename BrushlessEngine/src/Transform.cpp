#include "Transform.h"

Transform::Transform(GameObject* gameObject) : Component(gameObject) {
	this->position = float3();
	this->rotation = float3();
	this->scale = float3();
}