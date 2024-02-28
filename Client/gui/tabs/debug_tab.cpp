#include "debug_tab.hpp"
#include "../../imgui/imgui.h"
#include "../../user/state.hpp"

namespace DebugTab
{
	void Render()
	{
		if (ImGui::BeginTabItem("Debug"))
		{
			ImGui::Checkbox("Show Debug Visuals", &State.DebugVisuals);
			ImGui::EndTabItem();
		}
	}
}