#pragma once
#include "IExecute.h"
#include "Geometry.h"

class CameraDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> m_Shader;
	
	// Object
	shared_ptr<Geometry<VertexColorData>> m_Geometry;
	shared_ptr<VertexBuffer> m_VertexBuffer;
	shared_ptr<IndexBuffer> m_IndexBuffer;
	Matrix m_World = Matrix::Identity;

	// Camera
	shared_ptr<GameObject> m_Camera;
};

