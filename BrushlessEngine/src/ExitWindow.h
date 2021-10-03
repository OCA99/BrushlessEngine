#pragma once

#include "UIComponent.h"

class ExitWindow : public UIComponent
{
public:
	ExitWindow(Application* app, bool* enabled, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
};