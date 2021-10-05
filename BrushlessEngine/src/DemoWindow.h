#pragma once

#include "UIComponent.h"

class DemoWindow : public UIComponent
{
public:
	DemoWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
};