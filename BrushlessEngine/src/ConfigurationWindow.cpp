#include "ConfigurationWindow.h"
#include "ModuleEditor.h"
#include "Hardware.h"
#include "libraries/imgui/imgui.h"

#include <gl/GL.h>

ConfigurationWindow::ConfigurationWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status ConfigurationWindow::Update() {
	update_status ret = UPDATE_CONTINUE;

	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("Application"))
		{
			ImGui::InputText("Application name", app->editor->state.applicationName, IM_ARRAYSIZE(app->editor->state.applicationName));

			ImGui::SliderInt("FPS", &app->targetFPS, 1, 60, NULL, 0);

			ImGui::PlotHistogram("FPS", app->editor->state.log.frameLogs, 100, 0, ("FPS: " + std::to_string(ImGui::GetIO().Framerate)).c_str(), 0, 120.0f, ImVec2(ImGui::CalcItemWidth(), 70.0f));
			ImGui::PlotHistogram("MS", app->editor->state.log.frameMSLogs, 100, 0, ("MS: " + std::to_string(1000.0f / ImGui::GetIO().Framerate)).c_str(), 0, 120.0f, ImVec2(ImGui::CalcItemWidth(), 70.0f));

			ImGui::Checkbox("Console", &app->editor->state.consoleWindowOpen);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Window"))
		{
			ImGui::SliderInt("Window width", &app->editor->state.configuration.windowWidth, 600, 2560);
			ImGui::SliderInt("Window height", &app->editor->state.configuration.windowHeight, 400, 1440);
			ImGui::SliderFloat("Brightness", &app->editor->state.configuration.windowBrightness, 0.0f, 1.0f);

			ImGui::Checkbox("Fullscreen", &app->editor->state.configuration.fullscreen);

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Renderer"))
		{
			ImGui::Checkbox("Vsync", &app->editor->state.configuration.vsync);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("File System"))
		{
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Input"))
		{
			ImGui::Text("Mouse X: %0.0f", ImGui::GetIO().MousePos.x);
			ImGui::Text("Mouse Y: %0.0f", ImGui::GetIO().MousePos.y);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Hardware"))
		{
			Hardware* h = Hardware::GetHardware();

			ImGui::Text("SDL Version: %d.%d.%d", h->sdlVersion.major, h->sdlVersion.minor, h->sdlVersion.patch);
			ImGui::Text("OpenGL Version: %s", h->glVersion);

			ImGui::Separator();

			ImGui::Text("CPU Cores: %d", h->cpu.cpuCount);
			ImGui::Text("CPU Cache Line Size: %d", h->cpu.cpuCacheLineSize);

			ImGui::Separator();

			ImGui::Text("System RAM: %.2fGB", h->ram);

			ImGui::Separator();

			ImGui::Text("GPU Vendor: %d", h->gpu.vendor);
			ImGui::Text("GPU ID: %d", h->gpu.id);
			ImGui::Text("GPU Name: %ls", h->gpu.name.c_str());
			ImGui::Text("GPU Memory Budget: %lldMB", h->gpu.budget);
			ImGui::Text("GPU Memory Usage: %lldMB", h->gpu.usage);
			ImGui::Text("GPU Memory Available: %lldMB", h->gpu.available);
			ImGui::Text("GPU Memory Reserved: %lldMB", h->gpu.reserved);

			ImGui::Separator();

			CAPS c = h->caps;
			ImGui::Text("CAPS: %s%s%s%s%s%s%s%s%s%s%s", c._3DNow ? "3DNow, " : "", c.altiVec ? "AltiVec, " : "", c.avx ? "AVX, " : "", c.avx2 ? "AVX2, " : "", c.mmx ? "MMX, " : "", c.rdtsc ? "RDTSC, " : "", c.sse ? "SSE, " : "", c.sse2 ? "SSE2, " : "", c.sse3 ? "SSE3, " : "", c.sse41 ? "SSE41, " : "", c.sse42 ? "SSE42" : "");

			delete h;
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Open GL"))
		{
			ImGui::Checkbox("GL_DEPTH_TEST", &app->editor->state.configuration.opengl.depth);
			ImGui::Checkbox("GL_CULL_FACE", &app->editor->state.configuration.opengl.cull);
			ImGui::Checkbox("GL_LIGHTING", &app->editor->state.configuration.opengl.lighting);
			ImGui::Checkbox("GL_COLOR_MATERIAL", &app->editor->state.configuration.opengl.colorMaterial);
			ImGui::Checkbox("GL_TEXTURE_2D", &app->editor->state.configuration.opengl.texture2D);
			ImGui::Checkbox("WIREFRAME", &app->editor->state.configuration.opengl.wireframe);

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	return ret;
}