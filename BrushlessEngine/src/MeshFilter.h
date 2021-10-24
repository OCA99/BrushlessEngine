#pragma once

#include "Component.h"
#include "BrushlessMesh.h"

class MeshFilter : public Component {
public:
	MeshFilter(GameObject* gameObject);

	BrushlessMesh* mesh;
};