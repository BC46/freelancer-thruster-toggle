#pragma once

#include <windows.h>

extern DWORD thrustToggleReturnAddress;

extern BYTE isThrustOn;

/// @brief Ensures the Thruster activation can be toggled on/off using a single action.
void ThrustToggle();
