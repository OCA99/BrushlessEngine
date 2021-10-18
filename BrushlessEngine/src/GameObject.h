#pragma once

#include <string>

#include "Transform.h"

class GameObject {
public:
	GameObject(std::string name, bool active);

	Transform* transform;

	std::string name;
	bool active;
};