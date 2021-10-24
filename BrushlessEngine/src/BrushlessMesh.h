#pragma once

#include "glmath.h"
#include "Color.h"
#include "Component.h"
#include <vector>

class BrushlessMesh
{
public:

	BrushlessMesh();
	virtual	~BrushlessMesh();

	void			InitializeBuffers();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			DrawVertexNormals() const;
	void			DrawFaceNormals() const;

public:
	unsigned int indexBuffer = -1;
	int indexCount = -1;
	unsigned int* indices = nullptr;

	unsigned int vertexBuffer = -1;
	int vertexCount = -1;
	float* vertices = nullptr;

	unsigned int normalsBuffer = -1;
	float* normals = nullptr;
};