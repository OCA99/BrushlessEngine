#pragma once

#include "Component.h"
#include "BrushlessMesh.h"

class Application;

class MeshFilter : public Component {
public:
	MeshFilter(Application* app, GameObject* gameObject);

	void Init();

	BrushlessMesh* mesh;
};