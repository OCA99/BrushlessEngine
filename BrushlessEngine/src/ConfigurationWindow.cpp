#include "ConfigurationWindow.h"

ConfigurationWindow::ConfigurationWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status ConfigurationWindow::Update() {
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("Application"))
		{
			ImGui::InputText("Application name", app->editor->state.applicationName, IM_ARRAYSIZE(app->editor->state.applicationName));
			ImGui::Text("FPS: %.3f", ImGui::GetIO().Framerate);
			ImGui::Text("Milliseconds per frame: %.3f", 1000.0f / ImGui::GetIO().Framerate);

			bool bar = false;

			ImGui::SliderInt("FPS", &app->targetFPS, 1, 60, NULL, 0);
			ImGui::Checkbox("Console", &bar);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Window"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("File System"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Input"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Hardware"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Open GL"))
		{
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	return ret;
}