#include "MeshRenderer.h"

#include "glew.h"

#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TextureComponent.h"

#include "Application.h"

#include "libraries/imgui/imgui.h"

MeshRenderer::MeshRenderer(Application* app, GameObject* gameObject) : Component(app, gameObject, Component::COMPONENT_TYPE::MESH_RENDERER) {
}

void MeshRenderer::PostUpdate()
{
	InitRender();
	DrawVertices();
	DrawNormals();
	DrawTexture();
	BindIndices();
	ApplyTransform();
	DrawElements();
	if (settings.vertexNormals)
		DrawVertexNormals();
	if (settings.faceNormals)
		DrawFaceNormals();
	EndRender();
}

bool MeshRenderer::DrawInspector()
{
	if (ImGui::TreeNodeEx("Mesh Renderer"))
	{
		ImGui::Checkbox("Wireframe", &settings.wireframe);
		ImGui::Checkbox("Vertex Normals", &settings.vertexNormals);
		ImGui::Checkbox("Face Normals", &settings.faceNormals);

		ImGui::TreePop();
	}

	return true;
}

void MeshRenderer::InitRender()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	if (settings.wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void MeshRenderer::EndRender()
{
	glPopMatrix();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_NORMAL_ARRAY, 0);
	glBindBuffer(GL_TEXTURE_COORD_ARRAY, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	if (settings.wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void MeshRenderer::DrawVertices()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	for (int i = 0; i < meshFilter->meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshFilter->meshes[i]->vertexBuffer);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
	}
}

void MeshRenderer::DrawNormals()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	for (int i = 0; i < meshFilter->meshes.size(); i++)
	{
		glBindBuffer(GL_NORMAL_ARRAY, meshFilter->meshes[i]->normalsBuffer);
		glNormalPointer(GL_FLOAT, 0, NULL);
	}
}

void MeshRenderer::DrawTexture()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	Texture* texture = (Texture*)gameObject->GetComponent(Component::COMPONENT_TYPE::TEXTURE);
	for (int i = 0; i < meshFilter->meshes.size(); i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, meshFilter->meshes[i]->textureBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);
		glBindTexture(GL_TEXTURE_2D, texture->textureId);
	}
}

void MeshRenderer::BindIndices()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	for (int i = 0; i < meshFilter->meshes.size(); i++)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshFilter->meshes[i]->indexBuffer);
	}
}

void MeshRenderer::ApplyTransform()
{
	glPushMatrix();
	Transform* transform = (Transform*)gameObject->GetComponent(Component::COMPONENT_TYPE::TRANSFORM);
	glMultMatrixf(transform->transform.Transposed().ptr());
}

void MeshRenderer::DrawElements()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	for (int i = 0; i < meshFilter->meshes.size(); i++)
	{
		glDrawElements(GL_TRIANGLES, meshFilter->meshes[i]->indexCount, GL_UNSIGNED_INT, NULL);
	}
}

void MeshRenderer::DrawVertexNormals()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);

	for (auto mesh : meshFilter->meshes)
	{
		if (mesh->normalsBuffer == -1)
			continue;

		for (int i = 0; i < mesh->vertexCount * 3; i += 3)
		{
			glBegin(GL_LINES);
			glColor3f(1.f, 0.0f, 0.0f);

			glVertex3f(mesh->vertices[i], mesh->vertices[i + 1], mesh->vertices[i + 2]);
			glVertex3f(mesh->vertices[i] + mesh->normals[i] * 0.1f, mesh->vertices[i + 1] + mesh->normals[i + 1] * 0.1f, mesh->vertices[i + 2] + mesh->normals[i + 2] * 0.1f);
			glEnd();
		}
		
		glColor3f(1.0f, 1.0f, 1.0f);
	}
}

void MeshRenderer::DrawFaceNormals()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);

	for (auto mesh : meshFilter->meshes)
	{
		if (mesh->normalsBuffer == -1)
			continue;

		for (int i = 0; i < mesh->indexCount; i += 3)
		{
			glBegin(GL_LINES);
			glColor3f(0.0f, 1.f, 1.f);

			int vertexIndex1 = mesh->indices[i] * 3;
			int vertexIndex2 = mesh->indices[i + 1] * 3;
			int vertexIndex3 = mesh->indices[i + 2] * 3;
			float v0x = (mesh->vertices[vertexIndex1] + mesh->vertices[vertexIndex2] + mesh->vertices[vertexIndex3]) / 3;
			float v0y = (mesh->vertices[vertexIndex1 + 1] + mesh->vertices[vertexIndex2 + 1] + mesh->vertices[vertexIndex3 + 1]) / 3;
			float v0z = (mesh->vertices[vertexIndex1 + 2] + mesh->vertices[vertexIndex2 + 2] + mesh->vertices[vertexIndex3 + 2]) / 3;

			glVertex3f(v0x, v0y, v0z);

			float v1x = v0x + (mesh->normals[vertexIndex1] + mesh->normals[vertexIndex2] + mesh->normals[vertexIndex3]) / 3;
			float v1y = v0y + (mesh->normals[vertexIndex1 + 1] + mesh->normals[vertexIndex2 + 1] + mesh->normals[vertexIndex3 + 1]) / 3;
			float v1z = v0z + (mesh->normals[vertexIndex1 + 2] + mesh->normals[vertexIndex2 + 2] + mesh->normals[vertexIndex3 + 2]) / 3;

			glVertex3f(v1x, v1y, v1z);
			glEnd();
		}

		glColor3f(1.0f, 1.0f, 1.0f);

	}

}
