#include "main.h"
#include "utils.h"
#include "hooks.h"

const std::string commonModuleFileName = "common.dll";

DWORD thrustToggleFileOffset = 0x73C7D;
const int thrusterToggleInstructionSize = 6;

BOOL Start() {
    DWORD thrustToggleStartLocation = Utils::GetVirtualOffset(commonModuleFileName, thrustToggleFileOffset);

    // Set values in Hooks namespace
    thrustToggleReturnAddress = (DWORD) thrustToggleStartLocation + thrusterToggleInstructionSize;

    // If one of the hooks fail, return unsuccessful.
    if (!Utils::Hook(thrustToggleStartLocation, ThrustToggle, thrusterToggleInstructionSize)) {
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
