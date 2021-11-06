#pragma once

#include "Component.h"
#include <string>

class Application;

typedef unsigned char GLubyte;
class GameObject;

class Texture : public Component {
public:
	Texture(bool active = true);
	Texture(Application* app, GameObject* gameObject);
	Texture(std::string n, std::string p, unsigned int texId, unsigned int texBuf, int f, unsigned int fUnsigned, GLubyte* d, int w, int h, bool active);
	
	~Texture();

	bool DrawInspector();

	void SetTexture(const void* texture, unsigned int width, unsigned int height);
	void SetTexture(std::string path);
	bool SetTexture(Texture* texture);
	void SetDefaultTexture();
	void BindTexture(GLubyte* texData);
	GLubyte* SetCheckerboxTexture();

	void DeleteTexture();

public: 
	int format = -1;
	unsigned int formatUnsigned = -1;
	std::string name = "defaultTex";
	std::string texturePath = "Assets/Textures/";
	GLubyte* data = nullptr;
	int width, height = -1;

	unsigned int textureId = -1;
	unsigned int textureBuf = -1;
};