#pragma once

class GameObject;
class Application;

class Component {
public:
	enum class COMPONENT_TYPE {
		MESH_FILTER,
		MESH_RENDERER,
		TEXTURE,
		TRANSFORM
	};

	Component(Application* app, GameObject* gameObject, COMPONENT_TYPE type);

	virtual void Init() {};
	virtual void Update(float dt) {};
	virtual void PostUpdate() {};

	Application* app;
	GameObject* gameObject;
	COMPONENT_TYPE type;
};