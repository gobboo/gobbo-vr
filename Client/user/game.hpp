#pragma once
#include <cstdint>
#include "../il2cpp/il2cpp_resolver.hpp"

namespace VRC {
	inline uintptr_t Base = 0;
	inline uintptr_t GameAssembly = 0;
	inline uintptr_t UnityPlayer = 0;

	namespace LocalPlayer {
		inline Unity::CGameObject* Instance = nullptr;
		inline Unity::CCamera* Camera = nullptr;
		inline Unity::CTransform* Transform = nullptr;

		Unity::CGameObject* GetLocalPlayer();
		Unity::Vector3 GetLocalPosition();
	}

	namespace Util {
		Unity::CGameObject* FindBySubstring(const char* substring);
	}
}