#include "pch.h"
#include "03. ConstBufferDemo.h"
#include "GeometryHelper.h"

void ConstBufferDemo::Init()
{
	m_Shader = make_shared<Shader>(L"03. ConstBuffer.fx");

	m_Geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(m_Geometry, Color(0, 1, 0, 1));

	m_VertexBuffer = make_shared<VertexBuffer>();
	m_VertexBuffer->Create(m_Geometry->GetVertices());

	m_IndexBuffer = make_shared<IndexBuffer>();
	m_IndexBuffer->Create(m_Geometry->GetIndices());
}

void ConstBufferDemo::Update()
{
	auto dt = TIME->GetDeltaTime();

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		m_Translation.x -= 3.f * dt;
	}
	else if (INPUT->GetButton(KEY_TYPE::D))
	{
		m_Translation.x += 3.f * dt;
	}
	else if (INPUT->GetButton(KEY_TYPE::W))
	{
		m_Translation.y += 3.f * dt;
	}
	else if (INPUT->GetButton(KEY_TYPE::S))
	{
		m_Translation.y -= 3.f * dt;
	}

	// SRT
	m_World = Matrix::CreateTranslation(m_Translation);
}

void ConstBufferDemo::Render()
{
	m_Shader->GetMatrix("World")->SetMatrix((float*)&m_World);
	m_Shader->GetMatrix("View")->SetMatrix((float*)&m_View);
	m_Shader->GetMatrix("Projection")->SetMatrix((float*)&m_Projection);
	
	uint32 stride = m_VertexBuffer->GetStride();
	uint32 offset = m_VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, m_VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(m_IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	//m_Shader->Draw(0, 1, 3);
	m_Shader->DrawIndexed(0, 0, m_IndexBuffer->GetCount(), 0, 0);
}
