#pragma once

#include "UIComponent.h"

class ConsoleWindow : public UIComponent
{
public:
	ConsoleWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
};
