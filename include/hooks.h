#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Values that the hooks read
                // return addresses
extern DWORD    thrustToggleReturnAddress,
                checkThrusterReturnAddress,
                loadSceneReturnAddress,
                keyCmdNicknameCheckReturnAddress,
                playerThrustAddress,
                jmpFtolAddress,
                idsNameReturnAddress,
                keyUpStateReturnAddress,
                // function addresses
                iniReaderGetValueStringAddress,
                stricmpAddress;

// Moved values by the hooks
extern long newIdsName;

// Values that the hooks both read and write to
extern BYTE isThrustOn,
            hasBeenActivated,
            foundAfterburnNickname,
            keymapEditsComplete;

extern const char *afterburnNickname;

/// @brief Ensures the Thruster activation can be toggled on/off using a single action.
void ThrustToggleHook();

/// @brief Checks whether the Thruster has actually been activated.
void CheckThrusterHook();

/// @brief Disables the Thruster whenever a new scene is loaded.
void DisableThrusterHook();

/// @brief Checks via the nickname whether the afterburn key is being parsed in keymap.ini.
void UserAfterburnKeyCmdNicknameHook();

/// @brief Allows the ids_name value to be updated after the afterburn nickname has been found.
void UpdateIdsNameHook();

/// @brief Removes the keyup state in keymap.ini after the afterburn nickname has been found.
void RemoveKeyUpStateHook();
