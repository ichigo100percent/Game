#include "pch.h"
#include "StaticMeshDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "CameraScript.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"
#include "Model.h"
#include "ModelRenderer.h"

void StaticMeshDemo::Init()
{
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"15. Model.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform()->SetPosition(Vector3{ 0.f, 0.f, -5.f });
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());

	CreateTower();
	//CreateTank();

	RENDER->Init(_shader);
}

void StaticMeshDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		LightDesc lightDesc;
		lightDesc.ambient = Vector4(0.4f);
		lightDesc.diffuse = Vector4(1.f);
		lightDesc.specular = Vector4(0.f);
		lightDesc.direction = Vector3(1.f, 0.f, 1.f);
		RENDER->PushLightData(lightDesc);
	}

	{
		_obj->Update();
	}

	{

		if (INPUT->GetButton(KEY_TYPE::KEY_1))
		{
			_check = true;
		}
		else if (INPUT->GetButton(KEY_TYPE::KEY_2))
		{
			_check = false;
		}

		if (!_check)
		{
			_obj->GetModelRenderer()->SetPass(0);
		}
		else
		{
			_obj->GetModelRenderer()->SetPass(1);
		}
	}
}

void StaticMeshDemo::Render()
{

}

void StaticMeshDemo::CreateTower()
{
	// CustomData -> Memory
	shared_ptr<class Model> m1 = make_shared<Model>();
	//m1->ReadModel(L"Tower/Tower");
	//m1->ReadMaterial(L"Tower/Tower");
	m1->ReadModel(L"Ship/ship");
	m1->ReadMaterial(L"Ship/ship");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vector3(0, -20, 50));
	//_obj->GetOrAddTransform()->SetRotation(Vector3(90, 0, 0));
	_obj->GetOrAddTransform()->SetScale(Vector3(0.05f));

	_obj->AddComponent(make_shared<ModelRenderer>(_shader));
	{
		_obj->GetModelRenderer()->SetModel(m1);
		//_obj->GetModelRenderer()->SetPass(0);
	}
}

void StaticMeshDemo::CreateTank()
{
	// CustomData -> Memory
	shared_ptr<class Model> m1 = make_shared<Model>();
	m1->ReadModel(L"Tank/Tank");
	m1->ReadMaterial(L"Tank/Tank");

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform()->SetPosition(Vector3(0, 0, 50));
	_obj->GetOrAddTransform()->SetScale(Vector3(0.1f));

	_obj->AddComponent(make_shared<ModelRenderer>(_shader));
	{
		_obj->GetModelRenderer()->SetModel(m1);
		_obj->GetModelRenderer()->SetPass(0);
	}
}
