#include "main.h"
#include "utils.h"
#include "hooks.h"
#include "hook_manager.h"

BOOL Start()
{
    // Module and symbol names
    const std::string   commonModule =            "common.dll",
                        dacomModule =             "dacom.dll",
                        getValueStringSymbol =    "?get_value_string@INI_Reader@@QAEPBDXZ",
                        stricmpSymbol =           "stricmp";

    // Offsets
    const DWORD loadSceneOffset =       0x1B2A31,
                keyCmdNicknameOffset =  0x17671D,
                keyUpOffset =           0x1767F2,
                thrustToggleOffset =    0x073C7D,
                checkThrusterOffset =   0x03D240;

    // Values required by the hooks
    playerThrustAddress =               0x146CA6 + c_mainBase;
    iniReaderGetValueStringAddress =    Utils::GetProcOffset(commonModule, getValueStringSymbol);
    stricmpAddress =                    Utils::GetProcOffset(dacomModule, stricmpSymbol);

    // Register hooks and keep the return addresses
    HookManager hM;
    loadSceneReturnAddress =            hM.RegisterMainHook(loadSceneOffset,        DisableThrusterHook,                5);
    keyCmdNicknameCheckReturnAddress =  hM.RegisterMainHook(keyCmdNicknameOffset,   UserAfterburnKeyCmdNicknameHook,    6);
    keyUpStateReturnAddress =           hM.RegisterMainHook(keyUpOffset,            RemoveKeyUpStateHook,               5);

    thrustToggleReturnAddress =         hM.RegisterModuleHook(commonModule, thrustToggleOffset,     ThrustToggleHook,   6);
    checkThrusterReturnAddress =        hM.RegisterModuleHook(commonModule, checkThrusterOffset,    CheckThrusterHook,  5);

    // Return true/false based on whether all hooks have initialized successfully
    return hM.InitializeHooks();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpReserved);

    BOOL success = TRUE;

    if (fdwReason == DLL_PROCESS_ATTACH)
        success = Start();

    return success;
}
