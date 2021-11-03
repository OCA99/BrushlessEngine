#include "HierarchyWindow.h"
#include "BrushlessScene.h"
#include "GameObject.h"
#include "ModuleEditor.h"
#include "Application.h"

HierarchyWindow::HierarchyWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status HierarchyWindow::Update()
{
	update_status ret = UPDATE_CONTINUE;

	BrushlessScene* scene = app->editor->currentScene;

	DrawTreeNode(scene->objects);

	return ret;
}

void HierarchyWindow::DrawTreeNode(std::vector<GameObject*> objects)
{
	for (auto object : objects)
	{
		if (ImGui::TreeNodeEx(object->name.c_str()))
		{
			DrawTreeNode(object->children);
			ImGui::TreePop();
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{
			app->editor->selectedObject = object;
			app->editor->state.log.LOG("Selected object: %s", object->name.c_str());
		}
	}
}
