#pragma once

#include "Module.h"
//include "SDL.h"
#include "Mesh.h"

class Application;
struct aiMesh;

class ModuleImport : public Module
{
public:
	
	ModuleImport(Application* app, bool start_enabled = true);
	// Destructor
	virtual ~ModuleImport();

	bool Init();
	bool Start();
	bool CleanUp();

	uint ImportScene(const char* path);
	Mesh* ImportModel(aiMesh* mesh);

public:

	std::vector<Mesh*> listMesh;

private:

};
