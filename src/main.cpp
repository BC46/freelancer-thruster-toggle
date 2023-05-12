#include "main.h"
#include "utils.h"
#include "hooks.h"
#include "hook_manager.h"
#include "config_reader.h"

BOOL Start()
{
    const std::string configPath = "thruster_toggle.ini";

    // Config reading
    ConfigReader cr;
    ThrusterConfig tc;

    // Attempt to get the config, return FALSE if it fails
    if (!cr.GetConfig(configPath, tc))
        return FALSE;

    // Set the values based on the config information
    newIdsName = 1465;

    // Module names
    const std::string   commonModule =            "common.dll",
                        dacomModule =             "dacom.dll";

    // Offsets
    const DWORD loadSceneOffset =       0x1B2A31,
                keyCmdNicknameOffset =  0x17671D,
                keyUpOffset =           0x1767F2,
                idsNameOffset =         0x176774,
                thrustToggleOffset =    0x073C7D,
                checkThrusterOffset =   0x03D240;

    // Values required by the hooks
    playerThrustAddress =               0x146CA6 + c_mainBase;
    jmpFtolAddress =                    0x1B7EC0 + c_mainBase;
    iniReaderGetValueStringAddress =    Utils::GetProcOffset(commonModule,  "?get_value_string@INI_Reader@@QAEPBDXZ");
    stricmpAddress =                    Utils::GetProcOffset(dacomModule,   "stricmp");

    // Register hooks and keep the return addresses
    HookManager hm;
    loadSceneReturnAddress =            hm.RegisterMainHook(loadSceneOffset,        DisableThrusterHook,                5);
    keyCmdNicknameCheckReturnAddress =  hm.RegisterMainHook(keyCmdNicknameOffset,   UserAfterburnKeyCmdNicknameHook,    6);
    keyUpStateReturnAddress =           hm.RegisterMainHook(keyUpOffset,            RemoveKeyUpStateHook,               5);
    idsNameReturnAddress =              hm.RegisterMainHook(idsNameOffset,          UpdateIdsNameHook,                  5);

    thrustToggleReturnAddress =         hm.RegisterModuleHook(commonModule, thrustToggleOffset,     ThrustToggleHook,   6);
    checkThrusterReturnAddress =        hm.RegisterModuleHook(commonModule, checkThrusterOffset,    CheckThrusterHook,  5);

    // Return true/false based on whether all hooks have initialized successfully
    return hm.InitializeHooks();
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
