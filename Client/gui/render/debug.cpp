#include "debug.hpp"
#include "../../user/game.hpp"
#include <string>
#include <format> 
#include <iostream> 

namespace Debug
{
	void Render()
	{
		if (!VRC::LocalPlayer::Instance)
			return;

		std::string localPlayerHex = std::format("{:x}", (uintptr_t)VRC::LocalPlayer::Instance);

		RenderText("LocalPlayer - 0x" + localPlayerHex, ImVec2(10, 500), ImVec4(1, 1, 1, 1), true, false);

		Unity::Vector3 position = VRC::LocalPlayer::GetLocalPosition();
		std::string pos = "X: " + std::to_string(position.x) + " Y: " + std::to_string(position.y) + " Z: " + std::to_string(position.z);

		RenderText("Current Position - " + pos, ImVec2(10, 510), ImVec4(1, 1, 1, 1), true, false);
	}
}