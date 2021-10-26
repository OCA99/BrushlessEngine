#include "TextureComponent.h"

#include "glew.h"

#include "Application.h"
#include "ModuleImport.h"

Texture::Texture(Application* app, GameObject* gameObject) : Component(app, gameObject)
{
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

void Texture::SetTexture(const void* texture, unsigned int width, unsigned int height)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTexture(const char* path)
{
	glGenTextures(1, &textureId);
	unsigned int id = app->import->ImportTexture(textureId, path);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
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
