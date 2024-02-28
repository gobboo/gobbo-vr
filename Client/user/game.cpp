#include "game.hpp"
#include <iostream>

namespace VRC
{

	Unity::CGameObject* LocalPlayer::GetLocalPlayer()
	{
		if (Instance != nullptr)
			return Instance;

		Unity::CGameObject* player = Util::FindBySubstring("VRCPlayer[Local]");

		if (!player)
			return nullptr;

		Instance = player;
		Camera = Unity::Camera::GetMain();
		Transform = player->GetTransform();

		std::cout << "LocalPlayer - 0x" << std::hex << (uintptr_t)player << std::endl;

		return player;
	}

	Unity::Vector3 LocalPlayer::GetLocalPosition()
	{
		if (!Instance)
			return Unity::Vector3();

		return Transform->GetPosition();
	}

	Unity::CGameObject* Util::FindBySubstring(const char* substring)
	{
		// Obtain list
		Unity::il2cppArray<Unity::CGameObject*>* m_pObjects = Unity::GameObject::FindWithTag("Player");

		// Looping through list
		for (int i = 0; i < m_pObjects->m_uMaxLength; i++)
		{
			Unity::CGameObject* m_pObject = m_pObjects->operator[](i);

			if (!m_pObject) continue; // Just in-case

			// Obtaining object name and then converting it to std::string
			std::string m_sObjectName = m_pObject->GetName()->ToString();
			if (m_sObjectName.find(substring) != std::string::npos)
			{
				return m_pObject;
			}
		}
	}
}