#pragma once

#include "UIComponent.h"

class MainMenuBar : public UIComponent
{
public:
	MainMenuBar(Application* app, bool* enabled, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
};