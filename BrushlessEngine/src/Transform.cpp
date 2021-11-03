#include "Transform.h"
#include "Application.h"

Transform::Transform(Application* app, GameObject* gameObject) : Component(app, gameObject, Component::COMPONENT_TYPE::TRANSFORM) {
	this->transform = float4x4::identity;
}