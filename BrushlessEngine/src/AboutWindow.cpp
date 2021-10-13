#include "AboutWindow.h"

AboutWindow::AboutWindow(Application* app, std::string title, bool* open, ImGuiWindowFlags flags) : UIComponent(app, title, open, flags)
{}

update_status AboutWindow::Update()
{
	ImGui::Text("Brushless Engine");
	ImGui::Text("By Andres Sanchez and Oscar Cuatrecasas");
	ImGui::Text("3rd party libraries used:");
	ImGui::BulletText("SDL");
	ImGui::BulletText("ImGui");
	ImGui::BulletText("Glew");
	ImGui::BulletText("MathGeoLib");
	ImGui::BulletText("JSON");
	ImGui::Text("License:");
	ImGui::Text("MIT License\nCopyright(c) 2021 Andrés Sánchez, Oscar Cuatrecasas\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this softwareand associated documentation files(the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and /or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright noticeand this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");
	return UPDATE_CONTINUE;
}
