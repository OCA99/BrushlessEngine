#pragma once

#include "Component.h"

typedef unsigned char GLubyte;

class Texture : public Component {
public:
	Texture(GameObject* gameObject);
	~Texture();

	void SetTexture(const void* texture, unsigned int width, unsigned int height);
	void SetCheckerboxTexture();

	unsigned int textureId = 0;
};