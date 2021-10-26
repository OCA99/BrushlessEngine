#pragma once

#include "Component.h"
#include "glmath.h"

class Transform : public Component {
public:
	Transform(GameObject* gameObject);

	mat4x4 transform;
};