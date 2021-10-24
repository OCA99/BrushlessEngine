#pragma once

#include <string>

class Transform;
class MeshFilter;
class MeshRenderer;
class Texture;

class GameObject {
public:
	GameObject(std::string name, bool active);
	~GameObject();

	Transform* transform;
	MeshFilter* meshFilter;
	MeshRenderer* meshRenderer;
	Texture* texture;

	std::string name;
	bool active;
};