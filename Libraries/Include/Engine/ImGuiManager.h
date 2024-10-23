#pragma once

// ImGUI
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

class ImGuiManager
{
	DECLARE_SINGLE(ImGuiManager)
	
public:
	void Init();
	void Update();
	void Render();

};

