#include "GameObject.h"

#include "Application.h"
#include "ModuleImport.h"

#include "Transform.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "TextureComponent.h"

GameObject::GameObject(Application* app, std::string name, bool active = true) {
	this->name = name;
	this->active = active;
	
	this->transform = new Transform(app, this);
	this->meshFilter = new MeshFilter(app, this);
	this->meshRenderer = new MeshRenderer(app, this);
	this->texture = new Texture(app, this);
	this->texture->SetTexture("Assets/Textures/Lenna.png");
}

GameObject::~GameObject()
{
	delete transform;
	delete meshFilter;
	delete meshRenderer;
	delete texture;
}
