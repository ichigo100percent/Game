#pragma once
#include "IExecute.h"

class ImGuiDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

	void test();
private:
	bool show_demo_window = true;
	bool show_another_window = false;
	Vector4 clear_color = Vector4(0.f);
};

