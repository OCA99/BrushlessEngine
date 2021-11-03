#include "Transform.h"
#include "Application.h"

#include "libraries/imgui/imgui.h"

Transform::Transform(Application* app, GameObject* gameObject) : Component(app, gameObject, Component::COMPONENT_TYPE::TRANSFORM) {
	this->transform = float4x4::identity;
}

bool Transform::DrawInspector()
{
	if (ImGui::TreeNodeEx("Transform"))
	{
		float3 pos = getPosition();
		ImGui::Text("POSITION: ");
		ImGui::SameLine();
		ImGui::Text("x: %f", pos.x);
		ImGui::SameLine();
		ImGui::Text("y: %f", pos.y);
		ImGui::SameLine();
		ImGui::Text("z: %f", pos.z);

		Quat rot = getRotation();
		ImGui::Text("ROTATION: ");
		ImGui::SameLine();
		ImGui::Text("x: %f", rot.x);
		ImGui::SameLine();
		ImGui::Text("y: %f", rot.y);
		ImGui::SameLine();
		ImGui::Text("z: %f", rot.z);
		ImGui::SameLine();
		ImGui::Text("w: %f", rot.z);

		float3 scale = getScale();
		ImGui::Text("SCALE: ");
		ImGui::SameLine();
		ImGui::Text("x: %f", scale.x);
		ImGui::SameLine();
		ImGui::Text("y: %f", scale.y);
		ImGui::SameLine();
		ImGui::Text("z: %f", scale.z);
		
		ImGui::TreePop();
	}

	return true;
}

float3 Transform::getPosition()
{
	float3 pos, scale;
	Quat rot;

	transform.Decompose(pos, rot, scale);

	return pos;
}

float3 Transform::getScale()
{
	float3 pos, scale;
	Quat rot;

	transform.Decompose(pos, rot, scale);

	return scale;
}

Quat Transform::getRotation()
{
	float3 pos, scale;
	Quat rot;

	transform.Decompose(pos, rot, scale);

	return rot;
}
