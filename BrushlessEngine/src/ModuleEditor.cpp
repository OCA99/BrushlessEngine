#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleImport.h"

#include "ExitWindow.h"
#include "MainMenuBar.h"
#include "ConfigurationWindow.h"
#include "DemoWindow.h"
#include "ConsoleWindow.h"
#include "AboutWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"

#include "GameObject.h"
#include "BrushlessScene.h"
#include "MeshFilter.h"
#include "BrushlessNode.h"
#include "Transform.h"

#include <iostream>

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_internal.h"
#include "libraries/imgui/imgui_impl_sdl.h"
#include "libraries/imgui/imgui_impl_opengl2.h"
#include <gl/GL.h>

#include "libraries/json/json.hpp"

#include "Logger.hpp"
#include "DefaultLogger.hpp"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleEditor::~ModuleEditor()
{
	for (int i = 0; i < components.size(); i++) {
		delete components[i];
	}
	delete currentScene;
}

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

	Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);

	const unsigned int severity = Assimp::Logger::Debugging | Assimp::Logger::Info | Assimp::Logger::Err | Assimp::Logger::Warn;
	Assimp::DefaultLogger::get()->attachStream(new AssimpStream(&state.log), severity);

	state.log.Init();

	return ret;
}

bool ModuleEditor::Start()
{
	bool ret = true;

	glewInit();

	InitializeUI();
	LoadScene("Assets/BakerHouse.fbx");
	//LoadScene("Assets/monkey.fbx");

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

	std::vector<UIComponent*>::iterator it = components.begin();
	while (it != components.end()) {
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

	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

	ImGui::Render();
	// Render dear imgui into screen
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


	return UPDATE_CONTINUE;
}

void ModuleEditor::AddComponent(UIComponent* component)
{
	components.push_back(component);
}

void ModuleEditor::RemoveComponent(UIComponent* component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void ModuleEditor::LoadScene(const char* path)
{
	if (currentScene == nullptr) currentScene = new BrushlessScene();

	BrushlessNode* node = App->import->ImportScene(path);
	GameObject* object = CreateGameObject(node);
	currentScene->objects.push_back(object);
}

GameObject* ModuleEditor::CreateGameObject(BrushlessNode* node, GameObject* parent)
{
	GameObject* object = new GameObject(App, "New GameObject", true);
	object->parent = parent;
	MeshFilter* meshFilter = (MeshFilter*)object->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);

	for (int i = 0; i < node->meshes.size(); i++)
	{
		meshFilter->meshes.push_back(node->meshes[i]);
	}

	object->Init();

	for (int i = 0; i < node->children.size(); i++)
	{
		object->children.push_back(CreateGameObject(node->children[i], object));
	}

	Transform* transform = (Transform*)object->GetComponent(Component::COMPONENT_TYPE::TRANSFORM);
	transform->transform = float4x4(node->rot, node->position);

	object->name = node->name;

	return object;
}

bool ModuleEditor::CleanUp()
{
	components.clear();

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	Assimp::DefaultLogger::kill();

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
	AddComponent(new HierarchyWindow(App, "Hierarchy", &state.hierarachyWindowOpen, ImGuiWindowFlags_NoCollapse));
	AddComponent(new InspectorWindow(App, "Inspector", &state.inspectorWindowOpen, ImGuiWindowFlags_NoCollapse));
}

