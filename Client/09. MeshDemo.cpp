#include "pch.h"
#include "09. MeshDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Mesh.h"

void MeshDemo::Init()
{

	// Camera
	m_Camera = make_shared<GameObject>();
	m_Camera->GetOrAddTransform();
	m_Camera->AddComponent(make_shared<Camera>());
	m_Camera->AddComponent(make_shared<CameraScript>());

	m_Camera->GetTransform()->SetPosition(Vector3(0.f, 0.f, -2.0f));
	//m_Camera->GetTransform()->SetRotation(Vector3(25.f, 0.f, 0.f));

	m_Object = make_shared<GameObject>();
	m_Object->GetOrAddTransform();
	m_Object->AddComponent(make_shared<MeshRenderer>());
	{
		auto shader = make_shared<Shader>(L"07. Normal.fx");
		m_Object->GetMeshRenderer()->SetShader(shader);
	}
	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		m_Object->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
		m_Object->GetMeshRenderer()->SetTexture(texture);
	}
}

void MeshDemo::Update()
{
	m_Camera->Update();
	m_Object->Update();
}

void MeshDemo::Render()
{

}
