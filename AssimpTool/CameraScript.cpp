#include "pch.h"
#include "CameraScript.h"

void CameraScript::Start()
{
}

void CameraScript::Update()
{
	float dt = TIME->GetDeltaTime() * 2.f;

	Vector3 pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetLook() * m_Speed * dt;

	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetLook() * m_Speed * dt;

	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * m_Speed * dt;

	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * m_Speed * dt;

	GetTransform()->SetPosition(pos);

	if (INPUT->GetButton(KEY_TYPE::Q))
	{
		Vector3 rotation = GetTransform()->GetLocalRotation();
		rotation.x += dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::E))
	{
		Vector3 rotation = GetTransform()->GetLocalRotation();
		rotation.x -= dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::Z))
	{
		Vector3 rotation = GetTransform()->GetLocalRotation();
		rotation.y += dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}

	if (INPUT->GetButton(KEY_TYPE::C))
	{
		Vector3 rotation = GetTransform()->GetLocalRotation();
		rotation.y -= dt * 0.5f;
		GetTransform()->SetLocalRotation(rotation);
	}
}
