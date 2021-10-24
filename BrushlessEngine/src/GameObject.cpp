#include "GameObject.h"

#include "Transform.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"

GameObject::GameObject(std::string name, bool active = true) {
	this->name = name;
	this->active = active;

	this->transform = new Transform(this);
	this->meshFilter = new MeshFilter(this);
	this->meshRenderer = new MeshRenderer(this);
}

GameObject::~GameObject()
{
	delete transform;
	delete meshFilter;
	delete meshRenderer;
}
