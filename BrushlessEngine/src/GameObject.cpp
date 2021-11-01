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
	
	AddComponent(new Transform(app, this));
	AddComponent(new MeshFilter(app, this));
	AddComponent(new MeshRenderer(app, this));
	AddComponent(new Texture(app, this));
	((Texture*)GetComponent(Component::COMPONENT_TYPE::TEXTURE))->SetTexture("Assets/Textures/Lenna.png");
}

GameObject::~GameObject()
{
	for (auto c : components)
	{
		delete c;
	}

	components.clear();
}

void GameObject::Init()
{
	for (auto c : components)
	{
		c->Init();
	}
}

void GameObject::Update(float dt)
{
	for (auto c : components)
	{
		c->Update(dt);
	}
}

void GameObject::PostUpdate()
{
	for (auto c : components)
	{
		c->PostUpdate();
	}
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

Component* GameObject::GetComponent(Component::COMPONENT_TYPE type)
{
	for (auto c : components)
	{
		if (c->type == type) return c;
	}

	return nullptr;
}
