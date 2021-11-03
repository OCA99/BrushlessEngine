#pragma once

#include "Component.h"

class Application;

typedef unsigned char GLubyte;

class Texture : public Component {
public:
	Texture(Application* app, GameObject* gameObject);
	~Texture();

	bool DrawInspector();

	void SetTexture(const void* texture, unsigned int width, unsigned int height);
	void SetTexture(const char* path);
	void SetCheckerboxTexture();

	void DeleteTexture();

	const char* texturePath = nullptr;
	int width, height = 0;
	unsigned int textureId = 0;
};