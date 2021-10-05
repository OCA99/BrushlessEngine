#include "DemoWindow.h"

DemoWindow::DemoWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status DemoWindow::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status DemoWindow::Update() {
	update_status ret = UPDATE_CONTINUE;

	ImGui::ShowDemoWindow();

	return ret;
}

update_status DemoWindow::PostUpdate()
{
	return UPDATE_CONTINUE;
}
