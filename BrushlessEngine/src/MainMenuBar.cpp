#include "MainMenuBar.h"

MainMenuBar::MainMenuBar(Application* app, bool* enabled, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, enabled, title, open, flags)
{}

update_status MainMenuBar::PreUpdate() {
	if (ImGui::BeginMainMenuBar()) {
		return UPDATE_CONTINUE;
	}
	else {
		return UPDATE_STOP;
	}
}

update_status MainMenuBar::Update() {
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::BeginMenu("File"))
	{
		ImGui::MenuItem("Open", "cntr + l");
		ImGui::MenuItem("Save", "cntr + s");
		ImGui::MenuItem("Exit", "esc", &app->editor->state.exitWindowOpen);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Edit"))
	{
		ImGui::EndMenu();
	}

	return ret;
}

update_status MainMenuBar::PostUpdate() {
	ImGui::EndMainMenuBar();
	return UPDATE_CONTINUE;
}