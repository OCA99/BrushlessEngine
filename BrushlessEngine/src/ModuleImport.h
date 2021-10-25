#pragma once

#include "Module.h"
#include "BrushlessMesh.h"

#pragma warning(disable:4996)

class Application;
struct aiMesh;

class ModuleImport : public Module
{
public:
	ModuleImport(Application* app, bool start_enabled = true);
	virtual ~ModuleImport();

	bool Init();
	bool Start();
	bool CleanUp();

	std::vector<BrushlessMesh*> ImportScene(const char* path);
	BrushlessMesh* ImportMesh(aiMesh* mesh);
	unsigned int ImportTexture(unsigned int id, const char* path);

	wchar_t* GetWC(const char* c);
};