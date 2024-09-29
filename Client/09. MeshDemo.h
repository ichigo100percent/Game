#pragma once
#include "IExecute.h"
#include "Geometry.h"

class MeshDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	shared_ptr<Shader> m_Shader;
	
	shared_ptr<GameObject> m_Object;
	shared_ptr<GameObject> m_Camera;
};

