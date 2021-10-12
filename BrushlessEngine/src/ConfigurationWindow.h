#pragma once

#include "UIComponent.h"

class ConfigurationWindow : public UIComponent
{
public:
	ConfigurationWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
};