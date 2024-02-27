#pragma once

#include <stdint.h>
#include <dxgi.h>
#include <d3d11.h>
#include "../imgui/imgui.h"

typedef HRESULT(__stdcall* D3D_PRESENT_FUNCTION)(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

extern D3D_PRESENT_FUNCTION oPresent;
HRESULT __stdcall dPresent(IDXGISwapChain* __this, UINT SyncInterval, UINT Flags);

namespace DirectX
{
	extern HWND window;
	extern HANDLE hRenderSemaphore;
	void Shutdown();
	ImVec2 GetWindowSize();
}