#include "pch.h"
#include "02. QuadDemo.h"
#include "GeometryHelper.h"

void QuadDemo::Init()
{
	m_Shader = make_shared<Shader>(L"02. Quad.fx");

	m_Geometry = make_shared<Geometry<VertexColorData>>();
	GeometryHelper::CreateQuad(m_Geometry, Color(0, 1, 0, 1));

	m_VertexBuffer = make_shared<VertexBuffer>();
	m_VertexBuffer->Create(m_Geometry->GetVertices());

	m_IndexBuffer = make_shared<IndexBuffer>();
	m_IndexBuffer->Create(m_Geometry->GetIndices());
}

void QuadDemo::Update()
{
}

void QuadDemo::Render()
{
	uint32 stride = m_VertexBuffer->GetStride();
	uint32 offset = m_VertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, m_VertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(m_IndexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	//m_Shader->Draw(0, 1, 3);
	m_Shader->DrawIndexed(0, 1, m_IndexBuffer->GetCount(), 0, 0);
}
