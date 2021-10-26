#pragma once

#include "Component.h"
#include "glmath.h"

class Application;

class Transform : public Component {
public:
	Transform(Application* app, GameObject* gameObject);

	mat4x4 transform;
};