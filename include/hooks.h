#pragma once

#include <windows.h>

extern DWORD thrustToggleReturnAddress;
extern DWORD checkThrusterReturnAddress;
extern DWORD playerThrustAddress;
extern DWORD loadSceneReturnAddress;

extern BYTE isThrustOn;
extern BYTE hasBeenActivated;

/// @brief Ensures the Thruster activation can be toggled on/off using a single action.
void ThrustToggleHook();

/// @brief Checks whether the Thruster has actually been activated.
void CheckThrusterHook();

/// @brief Disables the Thruster whenever a new scene is loaded
void DisableThrusterHook();
