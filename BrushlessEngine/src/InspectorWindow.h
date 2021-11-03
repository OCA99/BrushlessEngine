#pragma once

#include "UIComponent.h"

class InspectorWindow : public UIComponent
{
public:
	InspectorWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
};