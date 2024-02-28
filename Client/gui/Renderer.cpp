#include "Renderer.hpp"
#include "RenderCmd.hpp"
#include "../hooks/directx.hpp"

static RenderCmdQueue s_CmdQueue;

void ImGuiRenderer::ExecuteQueue()
{
	WaitForSingleObject(DirectX::hRenderSemaphore, INFINITE);
	s_CmdQueue.Execute();
	ReleaseSemaphore(DirectX::hRenderSemaphore, 1, NULL);
}

RenderCmdQueue& ImGuiRenderer::GetCmdQueue()
{
	return s_CmdQueue;
}