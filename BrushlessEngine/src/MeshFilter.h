#pragma once

#include "Component.h"
#include "BrushlessMesh.h"
#include <vector>

class Application;

class MeshFilter : public Component {
public:
	MeshFilter(Application* app, GameObject* gameObject);

	void Init();
	bool DrawInspector();

	std::vector<BrushlessMesh*> meshes;
};