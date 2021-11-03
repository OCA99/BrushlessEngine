#include "MeshRenderer.h"

#include "glew.h"

#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TextureComponent.h"

#include "Application.h"

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
	EndRender();
}

void MeshRenderer::InitRender()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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
