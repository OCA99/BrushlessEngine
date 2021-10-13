#include "AboutWindow.h"

AboutWindow::AboutWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status AboutWindow::Update()
{
	if (ImGui::Button("Brushless Engine")) ShellExecuteA(NULL, "open", "https://github.com/OCA99/BrushlessEngine", NULL, NULL, SW_SHOWNORMAL);
	ImGui::Text("By Andres Sanchez and Oscar Cuatrecasas");
	ImGui::Text("3rd party libraries used:");
	if (ImGui::Button("SDL")) ShellExecuteA(NULL, "open", "https://www.libsdl.org/", NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::Button("ImGui")) ShellExecuteA(NULL, "open", "https://github.com/ocornut/imgui", NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::Button("Glew")) ShellExecuteA(NULL, "open", "https://github.com/nigels-com/glew", NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::Button("MathGeoLib")) ShellExecuteA(NULL, "open", "https://github.com/sheredom/json.h", NULL, NULL, SW_SHOWNORMAL);
	if (ImGui::Button("json.h")) ShellExecuteA(NULL, "open", "https://github.com/sheredom/json.h", NULL, NULL, SW_SHOWNORMAL);

	ImGui::Text("License:");
	ImGui::Text("MIT License\nCopyright(c) 2021 Andrés Sánchez, Oscar Cuatrecasas\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this softwareand associated documentation files(the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright noticeand this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");
	return UPDATE_CONTINUE;
}
