#include "ConsoleWindow.h"
#include "ModuleEditor.h"

ConsoleWindow::ConsoleWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status ConsoleWindow::Update()
{
	std::vector<std::string>* logs = app->editor->state.log.consoleLogs;

	for (int i = 0; i < logs->size(); i++) {
		ImGui::Text((*logs)[i].c_str());
	}

	return UPDATE_CONTINUE;
}
