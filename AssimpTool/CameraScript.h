#pragma once
#include "MonoBehaviour.h"

class CameraScript : public MonoBehaviour
{
public:
	virtual void Start() override;
	virtual void Update() override;

private:
	float m_Speed = 10.f;
};

