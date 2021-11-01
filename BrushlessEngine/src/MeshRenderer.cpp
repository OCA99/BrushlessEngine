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
	glBindBuffer(GL_ARRAY_BUFFER, meshFilter->mesh->vertexBuffer);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
}

void MeshRenderer::DrawNormals()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	glBindBuffer(GL_NORMAL_ARRAY, meshFilter->mesh->normalsBuffer);
	glNormalPointer(GL_FLOAT, 0, NULL);
}

void MeshRenderer::DrawTexture()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	Texture* texture = (Texture*)gameObject->GetComponent(Component::COMPONENT_TYPE::TEXTURE);
	glBindBuffer(GL_ARRAY_BUFFER, meshFilter->mesh->textureBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glBindTexture(GL_TEXTURE_2D, texture->textureId);
}

void MeshRenderer::BindIndices()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshFilter->mesh->indexBuffer);
}

void MeshRenderer::ApplyTransform()
{
	glPushMatrix();
	Transform* transform = (Transform*)gameObject->GetComponent(Component::COMPONENT_TYPE::TRANSFORM);
	glMultMatrixf(transform->transform.M);
	glPopMatrix();
}

void MeshRenderer::DrawElements()
{
	MeshFilter* meshFilter = (MeshFilter*)gameObject->GetComponent(Component::COMPONENT_TYPE::MESH_FILTER);
	glDrawElements(GL_TRIANGLES, meshFilter->mesh->indexCount, GL_UNSIGNED_INT, NULL);
}
