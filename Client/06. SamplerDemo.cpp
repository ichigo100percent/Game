#include "pch.h"
#include "06. SamplerDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"

void SamplerDemo::Init()
{
	m_Shader = make_shared<Shader>(L"05. Sampler.fx");

	m_Geometry = make_shared<Geometry<VertexTextureData>>();
	//GeometryHelper::CreateQuad(m_Geometry);
	//GeometryHelper::CreateCube(m_Geometry);
	//GeometryHelper::CreateSphere(m_Geometry);
	GeometryHelper::CreateGrid(m_Geometry, 256, 256);

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

	m_Texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");
}

void SamplerDemo::Update()
{
	m_Camera->Update();
}

void SamplerDemo::Render()
{
	m_Shader->GetMatrix("World")->SetMatrix((float*)&m_World);
	m_Shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	m_Shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	m_Shader->GetSRV("Texture0")->SetResource(m_Texture->GetComPtr().Get());

	enum ADDRESS_VALUE
	{
		ADDRESS_WRAP = 0,
		ADDRESS_MIRROR = 1,
		ADDRESS_CLAMP = 2,
		ADDRESS_BORDER = 3,
	};

	m_Shader->GetScalar("Address")->SetInt(ADDRESS_WRAP);

	uint32 stride = m_VertexBuffer->GetStride();
	uint32 offset = m_VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, m_VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(m_IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	//m_Shader->Draw(0, 1, 3);
	m_Shader->DrawIndexed(0, 0, m_IndexBuffer->GetCount(), 0, 0);
}
