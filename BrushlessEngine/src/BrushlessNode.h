#pragma once

#include "glmath.h"
#include "Color.h"
#include "Component.h"
#include <vector>
#include <string>
#include "glmath.h"
#include "libraries/MathGeoLib/include/Math/float3.h"
#include "libraries/MathGeoLib/include/Math/Quat.h"


class BrushlessMesh;

class BrushlessNode
{
public:

	BrushlessNode();
	virtual	~BrushlessNode();

	std::string name;

	std::vector<BrushlessNode*> children;
	std::vector<BrushlessMesh*> meshes;

	float3 position;
	float3 scale;
	Quat rot;
};