#pragma once

#include "UIComponent.h"

class AboutWindow : public UIComponent
{
public:
	AboutWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags);
	update_status Update() override;
};
