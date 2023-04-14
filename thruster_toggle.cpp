#include <windows.h>
#include <stdio.h>

BOOL Start() {
    BOOL result = TRUE;

    printf("Test");

    return result;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    UNREFERENCED_PARAMETER(hinstDLL);
    UNREFERENCED_PARAMETER(lpReserved);

    BOOL result = TRUE;

    if (fdwReason == DLL_PROCESS_ATTACH)
        result = Start();

    return result;
}
