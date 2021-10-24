#pragma once

#include <vector>

class GameObject;

class BrushlessScene {
public:
	BrushlessScene();
	~BrushlessScene();

	std::vector<GameObject*> objects;
};