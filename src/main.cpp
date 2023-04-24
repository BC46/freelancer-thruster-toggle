#include "main.h"
#include "utils.h"
#include "hooks.h"

const std::string commonModuleFileName = "common.dll";

const DWORD thrustToggleFileOffset = 0x73C7D;
const DWORD checkThrusterFileOffset = 0x3D240;
const DWORD loadSceneStartLocation = 0x5B2A31;

const int thrusterToggleInstructionSize = 6;
const int checkThrusterInstructionSize = 5;
const int loadSceneInstructionSize = 5;

BOOL Start() {
    DWORD thrustToggleStartLocation = Utils::GetVirtualOffset(commonModuleFileName, thrustToggleFileOffset);
    DWORD checkThrusterStartLocation = Utils::GetVirtualOffset(commonModuleFileName, checkThrusterFileOffset);

    // Set values for hooks
    thrustToggleReturnAddress = thrustToggleStartLocation + thrusterToggleInstructionSize;
    checkThrusterReturnAddress = checkThrusterStartLocation + checkThrusterInstructionSize;
    playerThrustAddress = 0x546CA6;
    loadSceneReturnAddress = loadSceneStartLocation + loadSceneInstructionSize;

    // If one of the hooks fail, return unsuccessful.
    if (!Utils::Hook(thrustToggleStartLocation, ThrustToggleHook, thrusterToggleInstructionSize) ||
        !Utils::Hook(checkThrusterStartLocation, CheckThrusterHook, checkThrusterInstructionSize) ||
        !Utils::Hook(loadSceneStartLocation, DisableThrusterHook, loadSceneInstructionSize)) {
        return FALSE;
    }

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpReserved);

    BOOL success = TRUE;

    if (fdwReason == DLL_PROCESS_ATTACH)
        success = Start();

    return success;
}
