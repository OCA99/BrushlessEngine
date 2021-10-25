#pragma once

class GameObject;
class Application;

class Component {
public:
	Component(Application* app, GameObject* gameObject);

	Application* app;
	GameObject* gameObject;
};