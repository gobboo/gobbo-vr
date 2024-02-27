#include "Renderer.h"
#include "RenderCmd.h"
#include "../hooks/directx.h"

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