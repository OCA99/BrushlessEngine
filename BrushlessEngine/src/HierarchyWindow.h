#pragma once

#include "UIComponent.h"
#include <vector>

class GameObject;

class HierarchyWindow : public UIComponent
{
public:
	HierarchyWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
	void DrawTreeNode(std::vector<GameObject*> objects);
};