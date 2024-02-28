// dllmain.cpp : Defines the entry point for the DLL application.
#include "user/main.hpp"
#include "gui/menu.hpp"
#include "kiero/kiero.h"
#include "hooks/directx.hpp"
#include <cstdio>
#include <iostream>
#include "il2cpp/il2cpp_resolver.hpp"
#include "user/game.hpp"
#include <future>

HMODULE hModule;
HANDLE hUnloadEvent;

void create_console() {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    // solve the disorder codes in the CJK character show
    SetConsoleOutputCP(CP_UTF8);
}

void GobboUpdate()
{
    VRC::LocalPlayer::GetLocalPlayer();
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    hModule = (HMODULE)lpReserved;
    hUnloadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

    bool isDXHooked = false;
    do
    {
        if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
        {
            create_console();

            // Initialize IL2CPP
            bool status = IL2CPP::Initialize();

            if (!status) {
                std::cout << "Failed to initialize IL2CPP" << std::endl;
                SetEvent(hUnloadEvent);
                break;
            }

            kiero::bind(8, (void**)&oPresent, dPresent);
            isDXHooked = true;
        }
    } while (!isDXHooked);

    IL2CPP::Callback::Initialize();
    IL2CPP::Callback::OnUpdate::Add(GobboUpdate);

    DWORD dwWaitResult = WaitForSingleObject(hUnloadEvent, INFINITE);
    if (dwWaitResult != WAIT_OBJECT_0)
    {
        std::cout << "Failed to wait for unload event" << std::endl;
        return FALSE;
	}

    IL2CPP::Callback::Uninitialize();

    kiero::shutdown();
    DirectX::Shutdown();
    fclose(stdout);
    FreeConsole();
    CloseHandle(hUnloadEvent);
    FreeLibraryAndExitThread(hModule, 0);

    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);

        CreateThread(0, 0, MainThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

