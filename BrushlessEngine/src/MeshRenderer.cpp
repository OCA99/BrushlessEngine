#include "MeshRenderer.h"

#include "glew.h"

#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TextureComponent.h"

#include "Application.h"

MeshRenderer::MeshRenderer(Application* app, GameObject* gameObject) : Component(app, gameObject) {
}

void MeshRenderer::Render()
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
	glBindBuffer(GL_ARRAY_BUFFER, gameObject->meshFilter->mesh->vertexBuffer);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
}

void MeshRenderer::DrawNormals()
{
	glBindBuffer(GL_NORMAL_ARRAY, gameObject->meshFilter->mesh->normalsBuffer);
	glNormalPointer(GL_FLOAT, 0, NULL);
}

void MeshRenderer::DrawTexture()
{
	glBindBuffer(GL_ARRAY_BUFFER, gameObject->meshFilter->mesh->textureBuffer);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	glBindTexture(GL_TEXTURE_2D, gameObject->texture->textureId);
}

void MeshRenderer::BindIndices()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObject->meshFilter->mesh->indexBuffer);
}

void MeshRenderer::ApplyTransform()
{
	glPushMatrix();
	glMultMatrixf(gameObject->transform->transform.M);
	glPopMatrix();
}

void MeshRenderer::DrawElements()
{
	glDrawElements(GL_TRIANGLES, gameObject->meshFilter->mesh->indexCount, GL_UNSIGNED_INT, NULL);
}
