#pragma once

#include <vector>
#include <algorithm>

#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class UIComponent;

struct EditorState {
	bool exitWindowOpen = false;
};

class ModuleEditor : public Module
{
public:
	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init();
	bool Start();

	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);

	void AddComponent(UIComponent* component);
	void RemoveComponent(UIComponent* component);

	bool CleanUp();

	std::vector<UIComponent*>* components = new std::vector<UIComponent*>();
	EditorState state;

private:
	void InitializeUI();
};
