#pragma once

#include "Component.h"
#include "glmath.h"
#include "libraries/MathGeoLib/include/Math/float4x4.h"

class Application;

class Transform : public Component {
public:
	Transform(Application* app, GameObject* gameObject);

	float4x4 transform;
};