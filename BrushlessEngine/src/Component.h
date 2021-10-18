#pragma once

class GameObject;

class Component {
public:
	Component(GameObject* gameObject);

	GameObject* gameObject;
};