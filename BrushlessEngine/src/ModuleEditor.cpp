#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

#include "ExitWindow.h"
#include "MainMenuBar.h"
#include "ConfigurationWindow.h"
#include "DemoWindow.h"
#include "ConsoleWindow.h"
#include "AboutWindow.h"

#include <iostream>

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_internal.h"
#include "libraries/imgui/imgui_impl_sdl.h"
#include "libraries/imgui/imgui_impl_opengl2.h"
#include <gl/GL.h>

#include "libraries/json/json.hpp"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init()
{
	bool ret = true;

	//INITIALIZE IMGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// TODO: Set optional io.ConfigFlags values, e.g. 'io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard' to enable keyboard controls.
	// TODO: Fill optional fields of the io structure later.
	// TODO: Load TTF/OTF fonts if you don't want to use the default font.
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	// Initialize helper Platform and Renderer backends (here we are using imgui_impl_win32.cpp and imgui_impl_dx11.cpp)
	ImGui_ImplOpenGL2_Init();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

	//Style Initialization
	ImGui::StyleColorsClassic();

	memset(state.applicationName, 0, 64);

	return ret;
}

bool ModuleEditor::Start()
{
	bool ret = true;

	InitializeUI();

	return ret;
}

static bool engineOpen = true;
static bool confirm = false;
update_status ModuleEditor::PreUpdate(float dt)
{
	// Feed inputs to dear imgui, start new frame
	ImGui_ImplSDL2_NewFrame();
	ImGui_ImplOpenGL2_NewFrame();

	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float dt)
{
	update_status ret = UPDATE_CONTINUE;

	std::vector<UIComponent*>::iterator it = components->begin();
	while (it != components->end()) {
		if ((*it)->open == nullptr || *(*it)->open) {
			if ((*it)->PreUpdate() == UPDATE_STOP) return UPDATE_STOP;
			if ((*it)->Update() == UPDATE_STOP) return UPDATE_STOP;
			if ((*it)->PostUpdate() == UPDATE_STOP) return UPDATE_STOP;
		}
		it++;
	}

	SDL_SetWindowSize(App->window->window, App->editor->state.configuration.windowWidth, App->editor->state.configuration.windowHeight);
	SDL_SetWindowBrightness(App->window->window, App->editor->state.configuration.windowBrightness);
	App->window->SetFullscreen(App->editor->state.configuration.fullscreen);
	App->renderer3D->SetVsync(App->editor->state.configuration.vsync);

	if (state.configuration.opengl.depth) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	if (state.configuration.opengl.cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	if (state.configuration.opengl.lighting) glEnable(GL_LIGHTING);
	else glDisable(GL_LIGHTING);

	if (state.configuration.opengl.colorMaterial) glEnable(GL_COLOR_MATERIAL);
	else glDisable(GL_COLOR_MATERIAL);

	if (state.configuration.opengl.texture2D) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);

	if (state.configuration.opengl.wireframe) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return ret;
}

update_status ModuleEditor::PostUpdate(float dt)
{
	// CREATE GRID
	glLineWidth(3.0f);

	glBegin(GL_LINES);
	glColor4f(0.8f, 0.8f, 0.8f, 0.8f);

	float d = 40.0f;

	for (float i = -d; i <= d; i += 2.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}
	glEnd();
	// END GRID

	GLfloat vertices[] = { 1, 1, 1,  -1, 1, 1,  -1,-1, 1,   1,-1, 1,   // v0,v1,v2,v3 (front)
						 1,-1,-1,   1, 1,-1,   // v4,v5 (right)
						 -1, 1,-1,   // v6 (top)
					   -1,-1,-1,   // v7 (left)
	};

	GLfloat normals[] = { 0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
						 1, 0, 0,   1, 0, 0,   // v4,v5 (right)
						   0, 1, 0,     // v6 (top)
						 -1, 0, 0,    // v7 (left)
	};

// color array
	GLfloat colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0,   1, 0, 1,   // v0,v1,v2,v3 (front)
							 0, 0, 1,   0, 1, 1,   // v4,v5 (right)
							 0, 1, 0,    // v6 (top)
							 0, 0, 0,   // v1,v6,v7,v2 (left)
	};

	GLubyte indices[] = { 0,1,2, 2,3,0,   // 36 of indices
						 0,3,4, 4,5,0,
						 0,5,6, 6,1,0,
						 1,6,7, 7,2,1,
						 7,4,3, 3,2,7,
						 4,7,6, 6,5,4 };

	// activate and specify pointer to vertex array
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	// draw a cube
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);

	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

	ImGui::Render();
	// Render dear imgui into screen
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


	return UPDATE_CONTINUE;
}

void ModuleEditor::AddComponent(UIComponent* component)
{
	components->push_back(component);
}

void ModuleEditor::RemoveComponent(UIComponent* component)
{
	components->erase(std::remove(components->begin(), components->end(), component), components->end());
}

bool ModuleEditor::CleanUp()
{
	components->clear();

	// Shutdown
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleEditor::InitializeUI()
{
	AddComponent(new ExitWindow(App, "Exit application?", &state.exitWindowOpen, ImGuiWindowFlags_NoCollapse));
	AddComponent(new MainMenuBar(App, "Title bar", nullptr, ImGuiWindowFlags_NoCollapse));
	AddComponent(new ConfigurationWindow(App, "Configuration", &state.configurationWindowOpen, ImGuiWindowFlags_NoCollapse));
	AddComponent(new DemoWindow(App, "Demo", &state.demoWindowOpen, ImGuiWindowFlags_NoCollapse));
	AddComponent(new ConsoleWindow(App, "Console", &state.consoleWindowOpen, ImGuiWindowFlags_NoCollapse));
	AddComponent(new AboutWindow(App, "About", &state.aboutWindowOpen, ImGuiWindowFlags_NoCollapse));
}

