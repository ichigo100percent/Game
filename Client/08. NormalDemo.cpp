#include "pch.h"
#include "08. NormalDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"

void NormalDemo::Init()
{
	m_Shader = make_shared<Shader>(L"07. Normal.fx");

	// Texture
	m_Texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");

	// Object
	m_Geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateSphere(m_Geometry);

	m_VertexBuffer = make_shared<VertexBuffer>();
	m_VertexBuffer->Create(m_Geometry->GetVertices());
	m_IndexBuffer = make_shared<IndexBuffer>();
	m_IndexBuffer->Create(m_Geometry->GetIndices());

	// Camera
	m_Camera = make_shared<GameObject>();
	m_Camera->GetOrAddTransform();
	m_Camera->AddComponent(make_shared<Camera>());
	m_Camera->AddComponent(make_shared<CameraScript>());

	m_Camera->GetTransform()->SetPosition(Vector3(0.f, 0.f, -2.0f));
	//m_Camera->GetTransform()->SetRotation(Vector3(25.f, 0.f, 0.f));

}

void NormalDemo::Update()
{
	m_Camera->Update();
}

void NormalDemo::Render()
{
	m_Shader->GetMatrix("World")->SetMatrix((float*)&m_World);
	m_Shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	m_Shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	m_Shader->GetSRV("Texture0")->SetResource(m_Texture->GetComPtr().Get());
	m_Shader->GetVector("LightDir")->SetFloatVector((float*)&m_LightDir);

	uint32 stride = m_VertexBuffer->GetStride();
	uint32 offset = m_VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, m_VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(m_IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	m_Shader->DrawIndexed(0, 0, m_IndexBuffer->GetCount(), 0, 0);
}
