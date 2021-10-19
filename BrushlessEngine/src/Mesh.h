#include "glmath.h"
#include "Color.h"
#include "Component.h"
#include <vector>

#include "libraries/Glew/include/glew.h"
#include "SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

enum MeshTypes
{
	Primitive_Grid,
	Primitive_Point,
	Primitive_Line,
	Primitive_Plane,
	Primitive_Cube,
	Primitive_Sphere,
	Primitive_Cylinder,
	Primitive_Pyramid,
	Custom_Mesh,
	Mult_Mesh,
};

class Mesh
{
public:

	Mesh();
	virtual	~Mesh();

	void			GenerateBuffers();

	virtual void	Render() const;
	virtual void	InnerRender() const;
	void			DrawVertexNormals() const;
	void			DrawFaceNormals() const;

	void			SetPos(float x, float y, float z);
	void			SetRotation(float angle, const vec3& u);
	void			Scale(float x, float y, float z);

	MeshTypes		GetType() const;

public:

	Color color;
	mat4x4 transform;
	bool axis, wire;

	uint indexBuf = -1; // index in VRAM
	int indexNum = -1;
	uint* indices = nullptr;

	uint vertexBuf = -1; // unique vertex in VRAM
	int vertexNum = -1; // = normalsNum
	float* vertices = nullptr;

	uint normalsBuf = -1;
	float* normals = nullptr;

	uint textureBuf = -1;
	uint textureID = -1;
	float* colors = nullptr;

	bool drawVertexNormals;
	bool drawFaceNormals;

protected:
	void			SetDefaultTexture();
	MeshTypes type;
};