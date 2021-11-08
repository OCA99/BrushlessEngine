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

//Primitives
PrimitiveCube::PrimitiveCube() : BrushlessMesh()
{
	primitiveType = Primitives::Primitive_Cube;


	vertices = new float[72]
	{
		//Low vertices
		-0.5f, -0.5f, -0.5f, //Bottom Left			1
		0.5f, -0.5f, -0.5f, //Bottom Right			2
		0.5f, -0.5f, 0.5f, //Top Right				3
		-0.5f, -0.5f, 0.5f, //Top Left				4

		//High vertices
		-0.5f, 0.5f, -0.5f, //Bottom Left			5
		0.5f, 0.5f, -0.5f, //Bottom Right			6
		0.5f, 0.5f, 0.5f, //Top Right				7
		-0.5f, 0.5f, 0.5f, //Top Left				8

		// Extra points for texcoords
		-0.5f, -0.5f, 0.5f, //Top Left				5
		-0.5f, -0.5f, -0.5f, //Bottom Left			1
		-0.5f, -0.5f, 0.5f, //Top Left				4
		0.5f, 0.5f, 0.5f, //Top Right				8

		-0.5f, -0.5f, 0.5f, //Top Left				5
		-0.5f, 0.5f, -0.5f, //Bottom Left			6
		0.5f, -0.5f, -0.5f, //Bottom Right			2
		-0.5f, -0.5f, -0.5f, //Bottom Left			1

		0.5f, -0.5f, -0.5f, //Bottom Right			2
		0.5f, 0.5f, -0.5f, //Bottom Right			6
		0.5f, 0.5f, -0.5f, //Bottom Right			7
		0.5f, -0.5f, 0.5f, //Top Right				3

		-0.5f, -0.5f, 0.5f, //Top Left				4
		0.5f, -0.5f, 0.5f, //Top Right				3
		0.5f, 0.5f, 0.5f, //Top Right				7
		0.5f, 0.5f, 0.5f, //Top Right				8
	};

	indices = new unsigned int[36]
	{
		// Faces
		0,1,2, 2,3,0, //Bottom
		3,2,6, 6,7,3, //Front
		2,1,5, 5,6,2, //Right
		7,4,0, 0,3,7, //Left
		1,0,4, 4,5,1, //Back
		5,4,7, 7,6,5 //Top
	};

	textureCoordinates = new float[48]
	{
		0.0f, 0.5f, //Top Left			5
		0.25f, 0.5f, //Bottom Left		1
		0.25f, 0.25f, //Top Left		4
		0.0f, 0.25f, //Top Right		8

		0.25f, 0.5f, //Bottom Left		1
		0.5f, 0.5f, //Bottom Right		2
		0.5f, 0.25f, //Top Right		3
		0.25f, 0.25f, //Top Left		4

		0.5f, 0.5f, //Bottom Right		2
		0.75f, 0.5f, //Bottom Right		6
		0.75f, 0.25f, //Bottom Right	7
		0.5f, 0.25f, //Top Right		3

		1.0f, 0.5f, //Bottom Left		5
		0.75f, 0.5f, //Bottom Right		6
		0.75f, 0.25f, //Top Right		7
		1.0f, 0.25f, //Top Left			8

		0.25f, 0.75f, //Top Left		5
		0.5f, 0.75f, //Bottom Left		6
		0.5f, 0.5f, //Bottom Right		2
		0.25f, 0.5f, //Bottom Left		1

		0.25f, 0.25f, //Top Left		4
		0.5f, 0.25f, //Top Right		3
		0.5f, 0.0f, //Top Right			7
		0.25f, 0.0f, //Top Right		8
	};

	vertexCount = 24;
	indexCount = 36;
}

PrimitivePlane::PrimitivePlane() : BrushlessMesh()
{
	primitiveType = Primitives::Primitive_Plane;

	vertices = new float[12]
	{
		-0.5f, 0.0f, -0.5f, //Bottom Left
		0.5f, 0.0f, -0.5f, //Bottom Right
		0.5f, 0.0f, 0.5f, //Top Right
		-0.5f, 0.0f, 0.5f, //Top Left
	};

	indices = new uint[6]{ 0,3,2, 2,1,0 };

	textureCoordinates = new float[8]
	{
		//Low vertices
		0.0f, 0.0f, //Bottom Left
		1.0f, 0.0f, //Bottom Right
		1.0f, 1.0f, //Top Right
		0.0f, 1.0f //Top Left
	};

	vertexCount = 4;
	indexCount = 6;
}


// PYRAMID ===========================================
PrimitivePyramid::PrimitivePyramid() : BrushlessMesh()
{
	primitiveType = Primitives::Primitive_Pyramid;

	vertices = new float[15]
	{
		// Top Vertex
		0.0f, 0.85f, 0.0f,

		// Bottom 
		-0.5f ,0.0f, -0.5f,
		0.5f ,0.0f, -0.5f,
		0.5f ,0.0f, 0.5f,
		-0.5f ,0.0f, 0.5f
	};

	indices = new unsigned int[18]
	{
		0, 4, 3,			// Front
		0, 3, 2,			// Left
		0, 2, 1,			// Right
		0, 1, 4,			// Back

		1, 3, 4,  1, 2, 3	// Bottom
	};

	textureCoordinates = new float[10]
	{
		//High vertex
		0.5f, 1.0f,

		//Low vertices
		0.0f, 0.0f,			// Bottom Left
		1.0f, 0.0f,			// Bottom Right
		0.0f, 0.0f,			// Top Right
		1.0f, 0.0f			// Top Left
	};

	vertexCount = 5;
	indexCount = 18;
}

PrimitiveCylinder::PrimitiveCylinder() : BrushlessMesh(), radius(1), height(1), sides(16)
{
	primitiveType = Primitives::Primitive_Cylinder;

	std::vector<float> verticesArray;

	//TOP CENTER
	verticesArray.push_back(0);
	verticesArray.push_back(height * 0.5f);
	verticesArray.push_back(0);
	float progression = 2 * M_PI / sides;
	float actualAngle = 0;

	//TOP FACE
	for (int i = 0; i < sides; i++)
	{
		verticesArray.push_back(radius * cos(actualAngle));	// Calculates the X value
		verticesArray.push_back(height * 0.5f);				// Calculates the Y value
		verticesArray.push_back(radius * sin(actualAngle));	// Calculates the Z value

		actualAngle -= progression;
	}

	actualAngle = 0;
	//BOTTOM CENTER
	verticesArray.push_back(0);
	verticesArray.push_back(-height * 0.5f);
	verticesArray.push_back(0);

	//BOTTOM FACE
	for (int i = 0; i < sides; i++)
	{
		verticesArray.push_back(radius * cos(actualAngle));	// Calculates the X value
		verticesArray.push_back(-height * 0.5f);				// Calculates the Y value
		verticesArray.push_back(radius * sin(actualAngle));	// Calculates the Z value

		actualAngle -= progression;
	}

	std::vector<uint> indicesArray;

	//TOP FACE
	for (int i = 1; i < sides; i++)
	{
		indicesArray.push_back(0);
		indicesArray.push_back(i);
		indicesArray.push_back(i + 1);
	}

	indicesArray.push_back(0);
	indicesArray.push_back(sides);
	indicesArray.push_back(1);

	//SIDES
	for (int i = 1; i < sides; i++)
	{
		// Left triangle
		indicesArray.push_back(i);
		indicesArray.push_back(sides + i + 1);
		indicesArray.push_back(sides + i + 2);

		// Right triangle
		indicesArray.push_back(i + sides + 2);
		indicesArray.push_back(i + 1);
		indicesArray.push_back(i);
	}

	indicesArray.push_back(sides);
	indicesArray.push_back(2 * sides + 1);
	indicesArray.push_back(sides + 2);
	indicesArray.push_back(sides + 2);
	indicesArray.push_back(1);
	indicesArray.push_back(sides);
	//BOTTOM FACE
	int sidesBuffer = sides + 1;
	for (int i = 1; i < sides; i++)
	{
		indicesArray.push_back(sidesBuffer);
		indicesArray.push_back(sidesBuffer + i + 1);
		indicesArray.push_back(sidesBuffer + i);
	}

	indicesArray.push_back(sidesBuffer);
	indicesArray.push_back(sides + 2);
	indicesArray.push_back(2 * sides + 1);

	// TODO: Texcoords

	vertexCount = verticesArray.size();
	vertices = new float[vertexCount]();

	for (size_t i = 0; i < vertexCount; i++)
	{
		vertices[i] = verticesArray[i];
	}

	indexCount = indicesArray.size();
	indices = new uint[indexCount]();

	for (size_t i = 0; i < indexCount; i++)
	{
		indices[i] = indicesArray[i];
	}

	verticesArray.clear();
	indicesArray.clear();
}

/*
// SPHERE ============================================
PrimitiveSphere::PrimitiveSphere(bool active) : MeshRenderer(active), radius(1), meshRings(12), quads(24)
{
	primitiveType = Primitives::Primitive_Sphere;
}

PrimitiveSphere::PrimitiveSphere(float _radius, uint _meshRings, uint _quads, bool active) : Mesh(active), radius(_radius), meshRings(_meshRings), quads(_quads)
{
	primitiveType = Primitives::Primitive_Sphere;
}
*/