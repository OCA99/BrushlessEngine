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

	void InitializeBuffers();

public:
	unsigned int vertexBuffer = 0;
	int vertexCount = -1;
	float* vertices = nullptr;

	unsigned int normalsBuffer = 0;
	float* normals = nullptr;

	unsigned int indexBuffer = 0;
	int indexCount = -1;
	unsigned int* indices = nullptr;

	unsigned int textureBuffer = 0;
	float* textureCoordinates = nullptr;

	std::vector<BrushlessMesh*> children;
};