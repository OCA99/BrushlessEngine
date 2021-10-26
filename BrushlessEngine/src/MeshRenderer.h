#pragma once

#include "Component.h"

class MeshRenderer : public Component {
public:
	MeshRenderer(GameObject* gameObject);

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