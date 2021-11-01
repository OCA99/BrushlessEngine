#include "MeshFilter.h"

#include "Application.h"

MeshFilter::MeshFilter(Application* app, GameObject* gameObject) : Component(app, gameObject, Component::COMPONENT_TYPE::MESH_FILTER)
{
}

void MeshFilter::Init()
{
	mesh->InitializeBuffers();
}
