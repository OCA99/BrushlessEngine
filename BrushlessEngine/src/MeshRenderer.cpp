#include "MeshRenderer.h"

#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#include "GameObject.h"
#include "MeshFilter.h"

MeshRenderer::MeshRenderer(GameObject* gameObject) : Component(gameObject) {
}

void MeshRenderer::Render()
{
	InitRender();
	DrawVertices();
	DrawNormals();
	BindIndices();
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

void MeshRenderer::BindIndices()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gameObject->meshFilter->mesh->indexBuffer);
}

void MeshRenderer::DrawElements()
{
	glDrawElements(GL_TRIANGLES, gameObject->meshFilter->mesh->indexCount, GL_UNSIGNED_INT, NULL);
}