#pragma once

#include "Component.h"
#include "libraries/MathGeoLib/include/Math/float3.h"

class Application;

class Transform : public Component {
public:
	Transform(Application* app, GameObject* gameObject);

	float3 position;
	float3 rotation;
	float3 scale;
};