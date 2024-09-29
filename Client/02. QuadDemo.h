#pragma once
#include "IExecute.h"
#include "Geometry.h"

class QuadDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> m_Shader;
	shared_ptr<Geometry<VertexColorData>> m_Geometry;
	shared_ptr<VertexBuffer> m_VertexBuffer;
	shared_ptr<IndexBuffer> m_IndexBuffer;
};

