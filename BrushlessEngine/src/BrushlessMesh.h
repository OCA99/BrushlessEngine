#pragma once

#include "glmath.h"
#include "Color.h"
#include "Component.h"
#include <vector>

class BrushlessMesh
{
public:
	enum class Primitives
	{
		Primitive_Plane,
		Primitive_Cylinder,
		Primitive_Sphere,
		Primitive_Pyramid,
		Primitive_Cube,
		NONE
	};

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

protected:
	Primitives primitiveType;
};

class PrimitivePlane : public BrushlessMesh
{
public:
	PrimitivePlane();
};

class PrimitiveCylinder : public BrushlessMesh
{
public:
	PrimitiveCylinder();
	PrimitiveCylinder(float _radius, float _height, unsigned int _sides, bool active = true);

	float radius;
	float height;
	unsigned int sides;
};

class PrimitiveSphere : public BrushlessMesh
{
public:
	PrimitiveSphere();
	PrimitiveSphere(float _radius, unsigned int _meshRings, unsigned int _quads, bool active = true);

	float radius;
	unsigned int meshRings;
	unsigned int quads;
};

class PrimitivePyramid : public BrushlessMesh
{
public:
	PrimitivePyramid();
};

class PrimitiveCube : public BrushlessMesh
{
public:
	PrimitiveCube();
};