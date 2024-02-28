#pragma once
#include <bitset>
#include <queue>
#include "keybinds.hpp"

class Settings {
public:

    //KeyBinds::Config KeyBinds = {
    //    VK_DELETE, // toggle menu
    //    VK_INSERT, // toggle radar
    //    VK_HOME, // toggle console
    //    VK_NEXT, // repair sabotage
    //    0x00, // noclip
    //    0x00, // close all doors
    //    0x00, // toggle zoom
    //    0x00, // toggle freecam
    //    0x00, // close current room door
    //    VK_END // toggle replay
    //};

    bool ImGuiInitialized = false;
    bool ShowMenu = false;

#ifdef _DEBUG
    bool DebugVisuals = false;
#endif

    bool AdjustByDPI = true;
    float dpiScale = 1.f;
    bool dpiChanged = false;

    std::string CurrentWorld;

    bool ShowConsole = false;


    // NOTE:
    // any code that modifies State.liveReplayEvents or any other collection should use the Replay.replayEventMutex
    // failure to do so will invalidate any existing iterator of any thread which will lead to rare and hard to diagnose crashes

    KeyBinds::Config KeyBinds = {
        VK_INSERT, // toggle menu
        VK_DELETE // toggle radar
    };


    Settings() {}

    void Load();
    void Save();
};

extern Settings State;