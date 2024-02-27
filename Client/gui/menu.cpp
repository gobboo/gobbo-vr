#include "menu.h"
#include "tabs/debug_tab.h"
#include "../imgui/imgui.h"
#include "../user/state.h"

namespace Menu
{
	void Init()
	{
		ImGui::SetNextWindowSize(ImVec2(400 * State.dpiScale, 300 * State.dpiScale), ImGuiCond_None);
		ImGui::SetNextWindowBgAlpha(1.f);
	}

	bool isInit = false;
	bool firstRender = true;
	void Render()
	{
		if (!isInit)
		{
			Init();
			isInit = true;
		}

		ImGui::Begin("Gobbo<3", &State.ShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
		ImGui::BeginTabBar("Gobbo#TopBar", ImGuiTabBarFlags_NoTabListScrollingButtons);

		DebugTab::Render();

		if (firstRender)
			firstRender = false;

		ImGui::EndTabBar();
		ImGui::End();
	}
}