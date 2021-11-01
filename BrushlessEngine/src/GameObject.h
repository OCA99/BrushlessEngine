#pragma once

#include <string>
#include <vector>

#include "Component.h"

class Application;
class Transform;
class MeshFilter;
class MeshRenderer;
class Texture;

class GameObject {
public:
	GameObject(Application* app, std::string name, bool active);
	~GameObject();

	void Init();
	void Update(float dt);
	void PostUpdate();

	void AddComponent(Component* component);
	Component* GetComponent(Component::COMPONENT_TYPE type);

	std::vector<Component*> components;

	std::string name;
	bool active;
};