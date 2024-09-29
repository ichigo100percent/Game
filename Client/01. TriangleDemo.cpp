#include "pch.h"
#include "01. TriangleDemo.h"

void TriangleDemo::Init()
{
	m_Shader = make_shared<Shader>(L"01. Triangle.fx");

	{
		m_Vertices.resize(3);

		m_Vertices[0].position = Vector3(-0.5f, 0.f, 0.f);
		m_Vertices[1].position = Vector3(0.f, 0.5f, 0.f);
		m_Vertices[2].position = Vector3(0.5f, 0.f, 0.f);
	}

	m_Buffer = make_shared<VertexBuffer>();
	m_Buffer->Create(m_Vertices);
}

void TriangleDemo::Update()
{
}

void TriangleDemo::Render()
{
	uint32 stride = m_Buffer->GetStride();
	uint32 offset = m_Buffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, m_Buffer->GetComPtr().GetAddressOf(), &stride, &offset);

	m_Shader->Draw(0, 1, 3);
}
