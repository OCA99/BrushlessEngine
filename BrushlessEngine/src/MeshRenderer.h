#pragma once

#include "Component.h"

class Application;

class MeshRenderer : public Component {
public:
	MeshRenderer(Application* app, GameObject* gameObject);

	void Render();
private:
	void InitRender();
	void EndRender();

	void DrawVertices();
	void DrawNormals();
	void DrawTexture();
	void BindIndices();
	void ApplyTransform();
	void DrawElements();
};