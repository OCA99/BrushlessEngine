#include "ConfigurationWindow.h"
#include "ModuleEditor.h"

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

			ImGui::SliderInt("FPS", &app->targetFPS, 1, 60, NULL, 0);
			ImGui::Checkbox("Console", &app->editor->state.consoleWindowOpen);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Window"))
		{
			ImGui::SliderInt("Window width", &app->editor->state.configuration.windowWidth, 600, 2560);
			ImGui::SliderInt("Window height", &app->editor->state.configuration.windowHeight, 400, 1440);
			ImGui::SliderFloat("Brightness", &app->editor->state.configuration.windowBrightness, 0.0f, 1.0f);

			SDL_SetWindowSize(app->window->window, app->editor->state.configuration.windowWidth, app->editor->state.configuration.windowHeight);
			SDL_SetWindowBrightness(app->window->window, app->editor->state.configuration.windowBrightness);

			ImGui::Checkbox("Fullscreen", &app->editor->state.configuration.fullscreen);
			app->window->SetFullscreen(app->editor->state.configuration.fullscreen);

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Renderer"))
		{
			ImGui::Checkbox("Vsync", &app->editor->state.configuration.vsync);
			app->renderer3D->SetVsync(app->editor->state.configuration.vsync);
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