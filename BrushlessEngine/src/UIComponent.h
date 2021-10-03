#pragma once

#include <string>

#include "Globals.h"
#include "Application.h"

#include "libraries/imgui/imgui.h"

class UIComponent {
public:
	Application* app;
	bool* enabled;
	std::string title;
	bool* open = nullptr;
	ImGuiWindowFlags flags;

	UIComponent(Application* app, bool* enabled, std::string title, bool* open, ImGuiWindowFlags flags) {
		this->app = app;
		this->enabled = enabled;
		this->title = title;
		this->open = open;
		this->flags = flags;
	}

	virtual update_status PreUpdate() {
		if (ImGui::Begin(title.c_str(), open, flags)) {
			return UPDATE_CONTINUE;
		}
		else {
			return UPDATE_STOP;
		}
	}

	virtual update_status Update() {
		return UPDATE_CONTINUE;
	}

	virtual update_status PostUpdate() {
		ImGui::End();
		return UPDATE_CONTINUE;
	}
};