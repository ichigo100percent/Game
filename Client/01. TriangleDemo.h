#pragma once
#include "IExecute.h"

class TriangleDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> m_Shader;
	vector<VertexData> m_Vertices;
	shared_ptr<VertexBuffer> m_Buffer;
};

