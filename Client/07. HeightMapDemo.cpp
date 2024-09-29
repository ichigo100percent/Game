#include "pch.h"
#include "07. HeightMapDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"

void HeightMapDemo::Init()
{
	m_Shader = make_shared<Shader>(L"06. Terrain.fx");

	// Texture
	m_HeightMap = RESOURCES->Load<Texture>(L"Height", L"..\\Resources\\Textures\\Terrain\\height.png");
	m_Texture = RESOURCES->Load<Texture>(L"Veigar", L"..\\Resources\\Textures\\veigar.jpg");

	const int32 width = m_HeightMap->GetSize().x;
	const int32 height = m_HeightMap->GetSize().y;

	const DirectX::ScratchImage& info = m_HeightMap->GetInfo();
	uint8* pixelBuffer = info.GetPixels();

	// Object
	m_Geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(m_Geometry, width, height);

	// CPU
	{
		vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(m_Geometry->GetVertices());

		for (int32 z = 0; z < height; z++)
		{
			for (int32 x = 0; x < width; x++)
			{
				int32 idx = width * z + x;
				uint8 height = pixelBuffer[idx] / 255.f * 25.f;
				v[idx].position.y = height; // 높이 보정
			}
		}
	}

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

void HeightMapDemo::Update()
{
	m_Camera->Update();
}

void HeightMapDemo::Render()
{
	m_Shader->GetMatrix("World")->SetMatrix((float*)&m_World);
	m_Shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	m_Shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	m_Shader->GetSRV("Texture0")->SetResource(m_Texture->GetComPtr().Get());

	uint32 stride = m_VertexBuffer->GetStride();
	uint32 offset = m_VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, m_VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(m_IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	m_Shader->DrawIndexed(0, 0, m_IndexBuffer->GetCount(), 0, 0);
}
