#pragma once

#include "Component.h"
#include <string>

class Application;

typedef unsigned char GLubyte;

class Texture : public Component {
public:
	Texture(Application* app, GameObject* gameObject);
	~Texture();

	bool DrawInspector();

	void SetTexture(const void* texture, unsigned int width, unsigned int height);
	void SetTexture(std::string path);
	void SetCheckerboxTexture();

	void DeleteTexture();

	std::string texturePath = "No texture";
	int width, height = 0;
	unsigned int textureId = 0;
};