#pragma once
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include <mutex>

void RenderText(std::string_view text, const ImVec2& pos, const ImVec4& color, const bool outlined, const bool centered);
void RenderLine(const ImVec2& start, const ImVec2& end, const ImVec4& color, bool shadow);
void RenderBox(const ImVec2& top, const ImVec2& bottom, const float height, const float width, const ImVec4& color, const bool wantsShadow);

typedef struct Drawing
{
	std::mutex m_DrawingMutex;

	// ImVec2 LocalPosition{ 0.0f, 0.0f };
} drawing_t;

class Visuals
{
public:
	static void Render();

	static drawing_t& GetDrawing() { return *s_Instance; }
private:
	static drawing_t* s_Instance;
};