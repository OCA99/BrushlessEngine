#pragma once

#include "Component.h"

class Application;

typedef unsigned char GLubyte;

class Texture : public Component {
public:
	Texture(Application* app, GameObject* gameObject);
	~Texture();

	void SetTexture(const void* texture, unsigned int width, unsigned int height);
	void SetTexture(const char* path);
	void SetCheckerboxTexture();

	unsigned int textureId = 0;
};