#include "Globals.h"
#include "Application.h"
#include "ModuleImport.h"

#include "libraries/Assimp/include/cimport.h"
#include "libraries/Assimp/include/scene.h"
#include "libraries/Assimp/include/postprocess.h"


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
	//ImportScene("Assets/warrior.fbx");
	ImportScene("Assets/BakerHouse.fbx");
	return true;
}

static bool engineOpen = true;
static bool confirm = false;


bool ModuleImport::CleanUp()
{
	

	return true;
}

uint ModuleImport::ImportScene(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (uint i = 0; i < scene->mNumMeshes; i++)
		{
			ImportModel(scene->mMeshes[i]);
		}
		aiReleaseImport(scene);
	}
	else
	{
		//error
	}

	return scene->mNumMeshes;
}

Mesh* ModuleImport::ImportModel(aiMesh* mesh)
{
	Mesh* m = new Mesh();
	m->vertexNum = mesh->mNumVertices;
	m->vertices = new float[m->vertexNum * 3];
	memcpy(m->vertices, mesh->mVertices, sizeof(float) * m->vertexNum * 3);

	//debug with vertices loaded

	if (mesh->HasFaces())
	{
		m->indexNum = mesh->mNumFaces * 3;
		m->indices = new uint[m->indexNum];
		for (uint j = 0; j < mesh->mNumFaces; j++)
		{
			if (mesh->mFaces[j].mNumIndices != 3)
			{
				// Quad
				//warning for geometry != 3 vertices
			}
			else
			{
				memcpy(&m->indices[j * 3], mesh->mFaces[j].mIndices, sizeof(uint) * 3);
			}
		}

		m->colors = new float[m->indexNum * 4]();	//RGBA
		m->normals = new float[mesh->mNumVertices * 3]();

		int t = 0;

		for (uint v = 0, n = 0, tx = 0, c = 0; v < mesh->mNumVertices; v++, n += 3, c += 4, tx += 2)
		{
			if (mesh->HasNormals())
			{
				m->normals[n] = mesh->mNormals[v].x;
				m->normals[n + 1] = mesh->mNormals[v].y;
				m->normals[n + 2] = mesh->mNormals[v].z;
			}

			if (mesh->HasVertexColors(v))
			{
				m->colors[c] = mesh->mColors[v]->r;
				m->colors[c + 1] = mesh->mColors[v]->g;
				m->colors[c + 2] = mesh->mColors[v]->b;
				m->colors[c + 3] = mesh->mColors[v]->a;
			}
			else
			{
				m->colors[c] = 0.0f;
				m->colors[c + 1] = 0.0f;
				m->colors[c + 2] = 0.0f;
				m->colors[c + 3] = 0.0f;
			}

			t = tx;
		}

		m->GenerateBuffers();

		listMesh.push_back(m);
		return m;
	}

	return nullptr;
}

