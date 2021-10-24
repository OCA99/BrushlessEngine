#include "Globals.h"
#include "Application.h"
#include "ModuleImport.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include "glew.h"

ModuleImport::ModuleImport(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleImport::~ModuleImport()
{}

bool ModuleImport::Init()
{
	bool ret = true;

	return ret;
}

bool ModuleImport::Start()
{
	glewInit();
	return true;
}

bool ModuleImport::CleanUp()
{


	return true;
}

std::vector<BrushlessMesh*> ModuleImport::ImportScene(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	std::vector<BrushlessMesh*> meshList;
	if (scene != nullptr && scene->HasMeshes())
	{
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			BrushlessMesh* mesh = ImportMesh(scene->mMeshes[i]);
			if (mesh != nullptr) meshList.push_back(mesh);
		}
		aiReleaseImport(scene);
	}
	else
	{
		App->editor->state.log.LOG("%s failed to load", path);
	}

	return meshList;
}

BrushlessMesh* ModuleImport::ImportMesh(aiMesh* aiMesh)
{
	BrushlessMesh* mesh = new BrushlessMesh();
	mesh->vertexCount = aiMesh->mNumVertices;
	mesh->vertices = new float[mesh->vertexCount * 3];
	memcpy(mesh->vertices, aiMesh->mVertices, sizeof(float) * mesh->vertexCount * 3);

	if (aiMesh->HasFaces())
	{
		mesh->indexCount = aiMesh->mNumFaces * 3;
		mesh->indices = new uint[mesh->indexCount];
		for (uint j = 0; j < aiMesh->mNumFaces; j++)
		{
			if (aiMesh->mFaces[j].mNumIndices != 3)
			{
				// https://github.com/mapbox/earcut.hpp
			}
			else
			{
				memcpy(&mesh->indices[j * 3], aiMesh->mFaces[j].mIndices, sizeof(uint) * 3);
			}
		}

		mesh->normals = new float[aiMesh->mNumVertices * 3]();

		for (uint i = 0; i < aiMesh->mNumVertices; i += 3)
		{
			if (aiMesh->HasNormals())
			{
				mesh->normals[i] = aiMesh->mNormals[i].x;
				mesh->normals[i + 1] = aiMesh->mNormals[i].y;
				mesh->normals[i + 2] = aiMesh->mNormals[i].z;
			}


		}

		mesh->textureCoordinates = new float[mesh->vertexCount * 2]();

		if (aiMesh->mTextureCoords[0])
		{
			for (uint i = 0; i < aiMesh->mNumVertices; i++)
			{
				mesh->textureCoordinates[i * 2] = aiMesh->mTextureCoords[0][i].x;
				mesh->textureCoordinates[i * 2 + 1] = aiMesh->mTextureCoords[0][i].y;
			}
		}

		return mesh;
	}

	delete mesh;

	return nullptr;
}
