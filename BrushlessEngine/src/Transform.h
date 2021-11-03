#pragma once

#include "Component.h"
#include "glmath.h"
#include "libraries/MathGeoLib/include/Math/float4x4.h"
#include "libraries/MathGeoLib/include/Math/float3.h"
#include "libraries/MathGeoLib/include/Math/Quat.h"

class Application;

class Transform : public Component {
public:
	Transform(Application* app, GameObject* gameObject);

	bool DrawInspector();

	float3 getPosition();
	float3 getScale();
	Quat getRotation();

	float4x4 transform;
};