#pragma once

#include <vector>
#include <algorithm>
#include <string>

#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "LogStream.hpp"

class UIComponent;
class BrushlessScene;
class GameObject;
class BrushlessMesh;
class BrushlessNode;

struct BrushlessLog {
	std::vector<std::string>* consoleLogs = new std::vector<std::string>();
	float frameLogs[100];
	int frameLogsIndex = 0;
	float frameMSLogs[100];
	int frameMSLogsIndex = 0;

	void Init() {
		memset(frameLogs, 0, 100);
		memset(frameMSLogs, 0, 100);
	}

	void LOG(const char* format, ...) {
		static char tmp_string[4096];
		static va_list ap;

		va_start(ap, format);
		vsprintf_s(tmp_string, 4096, format, ap);
		va_end(ap);
		consoleLogs->push_back(std::string(tmp_string));
	}

	void LOGDirect(const char* message) {
		consoleLogs->push_back(std::string(message));
	}

	void LOGFrames(float frames) {
		frameLogs[frameLogsIndex] = frames;
		if (frameLogsIndex <= 99) frameLogsIndex++;
		if (frameLogsIndex > 99) {
			for (int i = 0; i < 99; i++) {
				frameLogs[i] = frameLogs[i + 1];
			}
			frameLogsIndex--;
		}
	}

	void LOGMSFrames(float ms) {
		frameMSLogs[frameMSLogsIndex] = ms;
		if (frameMSLogsIndex <= 99) frameMSLogsIndex++;
		if (frameMSLogsIndex > 99) {
			for (int i = 0; i < 99; i++) {
				frameMSLogs[i] = frameMSLogs[i + 1];
			}
			frameMSLogsIndex--;
		}
	}
};

class AssimpStream : public Assimp::LogStream {
public:
	AssimpStream(BrushlessLog* log) {
		this->log = log;
	}

	~AssimpStream() {

	}

	void write(const char* message) {
		this->log->LOGDirect(message);
	}

private:
	BrushlessLog* log;
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
	BrushlessLog log;
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
	GameObject* CreateGameObject(BrushlessNode* node, GameObject* parent = nullptr);

	bool CleanUp();

	std::vector<UIComponent*> components;
	EditorState state;

	BrushlessScene* currentScene = nullptr;

private:
	void InitializeUI();
};
