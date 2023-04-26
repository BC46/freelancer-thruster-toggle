#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

/// @brief Gathers all the configs and hooks in order for the Thruster Toggle functionality to start working.
/// @return BOOL: Whether or not the functionality has been able to start.
BOOL Start();

/// @brief DLL main entry point.
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved);
