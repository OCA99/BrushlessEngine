#pragma once

#include "Module.h"
#include "BrushlessMesh.h"
#include "BrushlessNode.h"

#pragma warning(disable:4996)

class Application;
struct aiNode;
struct aiMesh;
struct aiScene;

class ModuleImport : public Module
{
public:
	ModuleImport(Application* app, bool start_enabled = true);
	virtual ~ModuleImport();

	bool Init();
	bool Start();
	bool CleanUp();

	BrushlessNode* ImportScene(const char* path);
	BrushlessNode* ImportNode(aiNode* node, const aiScene* aiScene);
	BrushlessMesh* ImportMesh(aiMesh* mesh);
	unsigned int ImportTexture(unsigned int id, const char* path);

	wchar_t* GetWC(const char* c);
};