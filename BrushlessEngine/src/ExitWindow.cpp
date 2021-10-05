#include "ExitWindow.h"

ExitWindow::ExitWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status ExitWindow::Update() {
	update_status ret = UPDATE_CONTINUE;

	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 100.0f);
	if (ImGui::Button("YES", ImVec2(75, 50)))
		ret = UPDATE_STOP;

	ImGui::NextColumn();
	if (ImGui::Button("NO", ImVec2(75, 50))) {
		*open = false;
	}

	return ret;
}