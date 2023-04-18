#pragma once

#include <windows.h>

class Utils {
public:
    /// @brief Allows the assembly code execution to be detoured to a custom function (hooking). This function is used to add additional features to a compiled binary.
    /// @param toHookLocation Memory adddress where the hook should be set.
    /// @param hookAddr Address of the custom function that has to be called in the hook.
    /// @param instructionLength Amount of bytes indicating the size of the instruction(s) that will be overwritten by the hook. Must be 5 or greater.
    /// @return BOOL: Whether or not the hook could be created.
    static BOOL Hook(void* toHookLocation, void* hookAddr, int instructionLength);
};