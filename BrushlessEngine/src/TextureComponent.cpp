#include "TextureComponent.h"

#include "glew.h"

#include "Application.h"
#include "ModuleImport.h"

#include "libraries/imgui/imgui.h"

Texture::Texture(Application* app, GameObject* gameObject) : Component(app, gameObject, Component::COMPONENT_TYPE::TEXTURE)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

bool Texture::DrawInspector()
{
	if (ImGui::TreeNodeEx("Texture"))
	{
		ImGui::Text("SIZE: %d, %d", width, height);
		ImGui::Text("PATH: %s", texturePath.c_str());

		if (ImGui::Button("Checkerbox"))
		{
			SetCheckerboxTexture();
		}

		ImGui::TreePop();
	}

	return true;
}

void Texture::SetTexture(const void* texture, unsigned int w, unsigned int h)
{
	DeleteTexture();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glBindTexture(GL_TEXTURE_2D, 0);

	width = w;
	height = h;

	texturePath = "Procedural Texture";
}

void Texture::SetTexture(std::string path)
{
	DeleteTexture();

	glGenTextures(1, &textureId);
	unsigned int id = app->import->ImportTexture(textureId, path.c_str());

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	texturePath = path;
}

void Texture::SetCheckerboxTexture()
{
	GLubyte texture[32][32][4];

	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			if ((i + j) % 2 == 0)
				texture[i][j][0] = texture[i][j][1] = texture[i][j][2] = 0;
			else
				texture[i][j][0] = texture[i][j][1] = texture[i][j][2] = 255;
			texture[i][j][3] = 255;
		}
	}

	SetTexture(texture, 32, 32);
}

void Texture::DeleteTexture()
{
	if (textureId != 0)
		glDeleteTextures(1, &textureId);
}
