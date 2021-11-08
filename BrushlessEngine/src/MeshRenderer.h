#pragma once

#include "Component.h"

class Application;
class GameObject;

class MeshRenderer : public Component {
public:
	MeshRenderer(Application* app, GameObject* gameObject);

	void PostUpdate();

	bool DrawInspector();
private:
	void InitRender();
	void EndRender();

	void DrawVertices();
	void DrawNormals();
	void DrawTexture();
	void BindIndices();
	void ApplyTransform();
	void DrawElements();
	void DrawVertexNormals();
	void DrawFaceNormals();

	struct Settings {
		bool wireframe = false;
		bool vertexNormals = false;
		bool faceNormals = false;
	};

	Settings settings;


};







