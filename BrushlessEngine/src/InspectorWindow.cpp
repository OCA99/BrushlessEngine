#include "InspectorWindow.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "GameObject.h"

InspectorWindow::InspectorWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status InspectorWindow::Update()
{
	GameObject* selected = app->editor->selectedObject;

	if (selected == nullptr)
	{
		ImGui::Text("No object selected");
		return UPDATE_CONTINUE;
	}

	ImGui::Text("%s", selected->name.c_str());
	ImGui::Separator();

	for (auto c : selected->components)
	{
		if (c->DrawInspector())
		{
			ImGui::Separator();
		}
	}

	return UPDATE_CONTINUE;
}
