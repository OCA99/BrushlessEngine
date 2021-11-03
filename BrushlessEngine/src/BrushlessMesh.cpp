#include "Globals.h"
#include "BrushlessMesh.h"

#include "glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>

// ------------------------------------------------------------
BrushlessMesh::BrushlessMesh() : vertexBuffer(-1), vertexCount(-1), vertices(nullptr), indexBuffer(-1), indexCount(-1), indices(nullptr),
normalsBuffer(-1)
{
}

BrushlessMesh::~BrushlessMesh()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vertexBuffer);
	delete vertices;
	vertices = nullptr;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &indexBuffer);
	delete indices;
	indices = nullptr;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &normalsBuffer);
	delete normals;
	normals = nullptr;

	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteBuffers(1, &textureBuffer);
}

void BrushlessMesh::InitializeBuffers()
{
	// Vertex
	glGenBuffers(1, (GLuint*)&vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, vertices, GL_STATIC_DRAW);

	// Normals
	glGenBuffers(1, &normalsBuffer);
	glBindBuffer(GL_NORMAL_ARRAY, normalsBuffer);
	glBufferData(GL_NORMAL_ARRAY, sizeof(float) * vertexCount * 3, normals, GL_STATIC_DRAW);

	// Textures
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 2, textureCoordinates, GL_STATIC_DRAW);

	// Indices
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexCount, indices, GL_STATIC_DRAW);
}