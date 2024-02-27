#include "debug_tab.h"
#include "../../imgui/imgui.h"

namespace DebugTab
{
	void Render()
	{
		if (ImGui::BeginTabItem("Debug"))
		{
			ImGui::Text("Debug tab");
			ImGui::EndTabItem();
		}
	}
}