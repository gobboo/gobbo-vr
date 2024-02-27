// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include "gui/menu.h"
#include "il2cpp/IL2CPP_Resolver.hpp"
#include "kiero/kiero.h"
#include "hooks/directx.h"

HMODULE hModule;
HANDLE hUnloadEvent;

void create_console() {
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    // solve the disorder codes in the CJK character show
    SetConsoleOutputCP(CP_UTF8);
}

void IL2Thread() {
    void* m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

    while (true) {
        if (GetAsyncKeyState(VK_DELETE) & 1) {
			SetEvent(hUnloadEvent);
			break;
		}

        m_pThisThread = IL2CPP::Thread::Attach(IL2CPP::Domain::Get());

        // Grab players and localplayer etc :)

        IL2CPP::Thread::Detach(m_pThisThread);
		Sleep(100);
	}

    // Free the thread
    IL2CPP::Thread::Detach(m_pThisThread);
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
    hModule = (HMODULE)lpReserved;
    hUnloadEvent = CreateEvent(0, 0, 0, 0);

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
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)IL2Thread, NULL, NULL, NULL);
            isDXHooked = true;
        }
    } while (!isDXHooked);

    DWORD dwWaitResult = WaitForSingleObject(hUnloadEvent, INFINITE);
    if (dwWaitResult != WAIT_OBJECT_0)
    {
        std::cout << "Failed to wait for unload event" << std::endl;
        return FALSE;
	}

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

