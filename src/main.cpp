#include "main.h"
#include "utils.h"
#include "hooks.h"
#include "hook_manager.h"

BOOL Start() {
    // Default values
    const std::string commonModule = "common.dll";
    const std::string getValueStringSymbol = "?get_value_string@INI_Reader@@QAEPBDXZ";

    const DWORD loadSceneOffset = 0x1B2A31;
    const DWORD keyCmdNicknameOffset = 0x17671D;
    const DWORD thrustToggleOffset = 0x73C7D;
    const DWORD checkThrusterOffset = 0x3D240;

    // Values required by the hooks
    playerThrustAddress = 0x146CA6 + c_mainBase;
    iniReaderGetValueStringAddress = Utils::GetProcOffset(commonModule, getValueStringSymbol);

    HookManager hookManager;

    // Register hooks and get the return addresses
    loadSceneReturnAddress =            hookManager.RegisterMainHook(loadSceneOffset,       DisableThrusterHook,                5);
    keyCmdNicknameCheckReturnAddress =  hookManager.RegisterMainHook(keyCmdNicknameOffset,  UserAfterburnKeyCmdNicknameCheck,   6);

    thrustToggleReturnAddress =         hookManager.RegisterModuleHook(commonModule,    thrustToggleOffset,     ThrustToggleHook,   6);
    checkThrusterReturnAddress =        hookManager.RegisterModuleHook(commonModule,    checkThrusterOffset,    CheckThrusterHook,  5);

    // Return true/false based on whether all hooks have initialized successfully
    return hookManager.InitializeHooks();
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpReserved);

    BOOL success = TRUE;

    if (fdwReason == DLL_PROCESS_ATTACH)
        success = Start();

    return success;
}
