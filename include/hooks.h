#pragma once

#include <windows.h>

extern DWORD thrustToggleReturnAddress;
extern DWORD checkThrusterReturnAddress;

extern BYTE isThrustOn;
extern BYTE hasBeenActivated;

/// @brief Ensures the Thruster activation can be toggled on/off using a single action.
void ThrustToggle();

/// @brief Checks whether the Thruster has actually been activated.
void CheckThruster();
