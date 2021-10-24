#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class UIComponent;
class BrushlessScene;

struct Log {
	std::vector<std::string>* consoleLogs = new std::vector<std::string>();

	void LOG(const char* format, ...) {
		static char tmp_string[4096];
		static va_list ap;

		va_start(ap, format);
		vsprintf_s(tmp_string, 4096, format, ap);
		va_end(ap);
		consoleLogs->push_back(std::string(tmp_string));
	}
};

struct OpenGLConfig {
	bool depth = true;
	bool cull = true;
	bool lighting = true;
	bool colorMaterial = true;
	bool texture2D = true;
	bool wireframe = false;
};

struct Configuration {
	int windowWidth = 1200;
	int windowHeight = 800;
	float windowBrightness = 1.0f;
	bool vsync = false;
	bool fullscreen = false;

	OpenGLConfig opengl;
};

struct EditorState {
	char applicationName[64];
	bool exitWindowOpen = false;
	bool configurationWindowOpen = false;
	bool demoWindowOpen = false;
	bool consoleWindowOpen = false;
	bool aboutWindowOpen = false;

	Configuration configuration;
	Log log;
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

	void LoadScene(const char* path);

	bool CleanUp();

	std::vector<UIComponent*> components;
	EditorState state;

	BrushlessScene* currentScene = nullptr;

private:
	void InitializeUI();
};
