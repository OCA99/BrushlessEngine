#pragma once

#include "Component.h"
#include "float3.h"

class Transform : public Component {
public:
	Transform(GameObject* gameObject);

	float3 position;
	float3 rotation;
	float3 scale;
};