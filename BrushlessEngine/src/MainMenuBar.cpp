#include "MainMenuBar.h"
#include "ModuleEditor.h"

MainMenuBar::MainMenuBar(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
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
		ImGui::MenuItem("Settings", nullptr, &app->editor->state.configurationWindowOpen);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Windows"))
	{
		ImGui::MenuItem("Hierarchy", nullptr, &app->editor->state.hierarachyWindowOpen);
		ImGui::MenuItem("Inspector", nullptr, &app->editor->state.inspectorWindowOpen);
		ImGui::MenuItem("Console", nullptr, &app->editor->state.consoleWindowOpen);
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Help"))
	{
		ImGui::MenuItem("Demo", nullptr, &app->editor->state.demoWindowOpen);
		ImGui::MenuItem("About", nullptr, &app->editor->state.aboutWindowOpen);
		ImGui::EndMenu();
	}

	return ret;
}

update_status MainMenuBar::PostUpdate() {
	ImGui::EndMainMenuBar();
	return UPDATE_CONTINUE;
}