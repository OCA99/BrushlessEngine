#pragma once

#include "glew.h"

#include "Globals.h"
#include "Timer.h"
#include "Module.h"

#include <vector>

class ModuleWindow;
class ModuleInput;
class ModuleRenderer3D;
class ModuleCamera3D;
class ModuleEditor;
class ModuleImport;

class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleEditor* editor;
	ModuleImport* import;

private:

	Timer	ms_timer;
	float	dt;
	std::vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	int targetFPS = 60;

private:
	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	int frameStart = 0;
};