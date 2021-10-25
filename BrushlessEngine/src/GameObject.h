#pragma once

#include <string>

class Application;
class Transform;
class MeshFilter;
class MeshRenderer;
class Texture;

class GameObject {
public:
	GameObject(Application* app, std::string name, bool active);
	~GameObject();

	Transform* transform;
	MeshFilter* meshFilter;
	MeshRenderer* meshRenderer;
	Texture* texture;

	std::string name;
	bool active;
};