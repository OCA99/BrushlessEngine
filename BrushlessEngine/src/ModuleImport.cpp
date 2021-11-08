#include "Globals.h"
#include "Application.h"
#include "ModuleImport.h"
#include "Gameobject.h"
#include "ModuleEditor.h"
#include "TextureComponent.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"


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
	ilInit();
	iluInit();
	ilutInit();
	App->editor->state.log.LOG("ilu Initialized");
	
	ilutRenderer(ILUT_OPENGL);
	return true;
}

bool ModuleImport::CleanUp()
{
	return true;
}

BrushlessNode* ModuleImport::ImportScene(const char* path)
{
	const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	BrushlessNode* node = nullptr;
	if (scene != nullptr && scene->HasMeshes())
	{
		node = ImportNode(scene->mRootNode, scene);
		aiReleaseImport(scene);
	}
	else
	{
		App->editor->state.log.LOG("%s failed to load", path);
	}

	return node;
}

BrushlessNode* ModuleImport::ImportNode(aiNode* node, const aiScene* scene)
{
	BrushlessNode* result = new BrushlessNode();

	for (int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		result->meshes.push_back(ImportMesh(mesh));
	}

	std::vector<BrushlessNode*> children;
	for (int i = 0; i < node->mNumChildren; i++)
	{
		children.push_back(ImportNode(node->mChildren[i], scene));
	}

	result->children = children;

	aiVector3D translation, scaling;
	aiQuaternion rotation;

	node->mTransformation.Decompose(scaling, rotation, translation);

	result->position = float3(translation.x, translation.y, translation.z);
	result->scale = float3(scaling.x, scaling.y, scaling.z);
	result->rot = Quat(rotation.x, rotation.y, rotation.z, rotation.w);

	result->name = node->mName.C_Str();

	return result;
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

Texture* ModuleImport::ImportTexture(const char* path)
{
	uint id = 0;
	ilGenImages(1, &id);
	ilBindImage(id);

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	Texture* texture = new Texture();

	if (id == 0)
		App->editor->state.log.LOG("Error");

	if (ilLoadImage((const ILstring)path))
	{
		if (ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			ILenum error = ilGetError();

			if (error != IL_NO_ERROR)
			{
				App->editor->state.log.LOG("Texture error: %d, %s", error, iluErrorString(error));
			}
			else
			{
				App->editor->state.log.LOG("Texture loaded successfully from: %s", path);

				texture->textureId = id;
				texture->data = ilGetData();
				texture->width = ilGetInteger(IL_IMAGE_WIDTH);
				texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
				texture->format = texture->formatUnsigned = ilGetInteger(IL_IMAGE_FORMAT);
				texture->texturePath = path;
			}
		}
		else
		{
			App->editor->state.log.LOG("Error converting texture: %d, %s", ilGetError(), iluErrorString(ilGetError()));
		}
	}
	else
	{
		App->editor->state.log.LOG("Error loading the texture from %s: %d, %s", path, ilGetError(), iluErrorString(ilGetError()));
	}

	return texture;
}

wchar_t* ModuleImport::GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}
