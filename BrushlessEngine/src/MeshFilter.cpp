#include "MeshFilter.h"

#include "Application.h"

#include "libraries/imgui/imgui.h"

MeshFilter::MeshFilter(Application* app, GameObject* gameObject) : Component(app, gameObject, Component::COMPONENT_TYPE::MESH_FILTER)
{
}

void MeshFilter::Init()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->InitializeBuffers();
	}
}

bool MeshFilter::DrawInspector()
{
	if (ImGui::TreeNodeEx("Mesh Filter"))
	{
		for (auto mesh : meshes)
		{
			if (ImGui::TreeNodeEx("Mesh"))
			{
				ImGui::Text("Vertices: %d", mesh->vertexCount);
				ImGui::Text("Faces: %d", mesh->indexCount / 3);

				ImGui::TreePop();
			}
		}

		ImGui::TreePop();
	}

	return true;
}
