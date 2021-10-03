#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"

#include "ExitWindow.h"
#include "MainMenuBar.h"

#include <iostream>

#include "libraries/imgui/imgui.h"
#include "libraries/imgui/imgui_internal.h"
#include "libraries/imgui/imgui_impl_sdl.h"
#include "libraries/imgui/imgui_impl_opengl2.h"

#include "libraries/json/json.hpp"

ModuleEditor::ModuleEditor(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init()
{
	LOG("Creating Editor Context");
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
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/brandon.ttf", 25.0f);
	//io.Fonts->AddFontFromFileTTF("Assets/Fonts/Ephesis-Regular.ttf", 25.0f);
	//io.Fonts->AddFontFromFileTTF("Assets/Fonts/font.ttf", 25.0f);
	//io.Fonts->AddFontFromFileTTF("Assets/Fonts/Rajdhani-Medium.ttf", 25.0f);

	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  //This Enables Using multiple view ports

	//ImGui::SmallButton("Exit");

	// Initialize helper Platform and Renderer backends (here we are using imgui_impl_win32.cpp and imgui_impl_dx11.cpp)
	ImGui_ImplOpenGL2_Init();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer3D->context);

	//Style Initialization
	ImGui::StyleColorsClassic();

	return ret;
}

bool ModuleEditor::Start()
{
	LOG("Setting up the editor");
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
		if ((*it)->enabled == nullptr || *(*it)->enabled) {
			if ((*it)->PreUpdate() == UPDATE_STOP) return UPDATE_STOP;
			if ((*it)->Update() == UPDATE_STOP) return UPDATE_STOP;
			if ((*it)->PostUpdate() == UPDATE_STOP) return UPDATE_STOP;
		}
		it++;
	}

	return ret;
}

update_status ModuleEditor::PostUpdate(float dt)
{
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
	LOG("Cleaning editor");

	components->clear();

	// Shutdown
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

void ModuleEditor::InitializeUI()
{
	AddComponent(new ExitWindow(App, &state.exitWindowOpen, "Exit application?", nullptr, ImGuiWindowFlags_NoCollapse));
	AddComponent(new MainMenuBar(App, nullptr, "Title bar", nullptr, ImGuiWindowFlags_NoCollapse));
}

