#pragma once

#include <string>

class Transform;
class MeshFilter;
class MeshRenderer;

class GameObject {
public:
	GameObject(std::string name, bool active);
	~GameObject();

	Transform* transform;
	MeshFilter* meshFilter;
	MeshRenderer* meshRenderer;

	std::string name;
	bool active;
};