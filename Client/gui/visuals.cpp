#include "visuals.hpp"
#include "../user/state.hpp"
#include "render/debug.hpp"
#include "../user/util.hpp"
#include <string_view>

drawing_t* Visuals::s_Instance = new drawing_t();
ImGuiWindow* CurrentWindow = nullptr;

void RenderText(std::string_view text, const ImVec2& pos, const ImVec4& color, const bool outlined = true, const bool centered = true)
{
	if (text.empty()) return;
	ImVec2 ImScreen = pos;
	if (centered)
	{
		auto size = ImGui::CalcTextSize(text.data(), text.data() + text.length());
		ImScreen.x -= size.x * 0.5f;
		ImScreen.y -= size.y;
	}

	if (outlined)
	{
		CurrentWindow->DrawList->AddText(nullptr, 0.f,
			ImVec2(ImScreen.x + 0.5f * State.dpiScale, ImScreen.y + 0.5f * State.dpiScale),
			ImGui::GetColorU32(IM_COL32_BLACK), text.data(), text.data() + text.length());
	}

	CurrentWindow->DrawList->AddText(nullptr, 0.f, ImScreen, ImGui::GetColorU32(color), text.data(), text.data() + text.length());
}

void RenderLine(const ImVec2& start, const ImVec2& end, const ImVec4& color, bool shadow = false)
{
	if (shadow)
	{
		CurrentWindow->DrawList->AddLine(
			ImVec2(start.x + 0.5f * State.dpiScale, start.y + 0.5f * State.dpiScale),
			ImVec2(end.x + 0.5f * State.dpiScale, end.y + 0.5f * State.dpiScale),
			ImGui::GetColorU32(color) & IM_COL32_A_MASK, 1.0f * State.dpiScale);
	}

	CurrentWindow->DrawList->AddLine(start, end, ImGui::GetColorU32(color), 1.0f * State.dpiScale);
}

void RenderBox(const ImVec2& top, const ImVec2& bottom, const float height, const float width, const ImVec4& color, const bool wantsShadow = true)
{
	const ImVec2 points[] = {
		bottom, { bottom.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) },
		{ bottom.x - 0.5f * State.dpiScale, bottom.y }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), bottom.y },

		{ top.x + 0.5f * State.dpiScale, bottom.y }, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), bottom.y },
		{ top.x, bottom.y }, { top.x, ((float)(int)(bottom.y * 0.75f + top.y * 0.25f)) },

		{ bottom.x, top.y }, { bottom.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) },
		{ bottom.x - 0.5f * State.dpiScale, top.y }, { ((float)(int)(bottom.x * 0.75f + top.x * 0.25f)), top.y },

		top, { ((float)(int)(top.x * 0.75f + bottom.x * 0.25f)), top.y },
		{ top.x, top.y + 0.5f * State.dpiScale }, { top.x, ((float)(int)(top.y * 0.75f + bottom.y * 0.25f)) }
	};

	if (wantsShadow) {
		const ImVec4& shadowColor = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(color) & IM_COL32_A_MASK);
		for (size_t i = 0; i < std::size(points); i += 2) {
			RenderLine(ImVec2(points[i].x + 0.5f * State.dpiScale, points[i].y + 0.5f * State.dpiScale), ImVec2(points[i].x + 0.5f * State.dpiScale, points[i].y + 0.5f * State.dpiScale), shadowColor, false);
		}
	}
	for (size_t i = 0; i < std::size(points); i += 2) {
		RenderLine(points[i], points[i + 1], color, false);
	}
}

void Visuals::Render() {
	CurrentWindow = ImGui::GetCurrentWindow();

	drawing_t& instance = Visuals::GetDrawing();

	synchronized(instance.m_DrawingMutex) {
		if (State.DebugVisuals) {
			Debug::Render();
		}
	};
}