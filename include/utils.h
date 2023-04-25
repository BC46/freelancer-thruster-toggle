#pragma once

#include <windows.h>
#include <string>
#include <map>

/// @brief Base address of the main module.
extern const DWORD c_mainBase;

class Utils
{
private:
    /// @brief Acts as a module handle cache. The modules are identified by their name in string format.
    static std::map<std::string, HMODULE> modules;

    /// @brief Tries to find a cached module handle. If it hasn't been cached yet, it'll be added and returned.
    /// @param moduleName Name of the module that should be searched for.
    /// @return HMODULE: Handle of the requested module.
    static HMODULE FindModuleHandle(const std::string &moduleName);

public:
    /// @brief Returns the virtual address of the file offset which will be located in the memory.
    /// @param module Name of the module where the offset is located.
    /// @param fileOffset The offset as if it was located using a hex editor.
    /// @return DWORD: Virtual offset
    static DWORD GetVirtualOffset(const std::string &module, DWORD fileOffset);

    /// @brief Returns the virtual address of a symbol/proc in a specific module.
    /// @param module Name of the module where the symbol/proc resides.
    /// @param symbol Symbol of the proc that should be retrieved.
    /// @return DWORD: Proc offset
    static DWORD GetProcOffset(const std::string &module, const std::string &symbol);

    /// @brief Allows the assembly code execution to be detoured to a custom function (hooking). This function is used to add additional features to a compiled binary.
    /// @param toHookLocation Memory address where the hook should be set.
    /// @param hookAddr Address of the custom function that has to be called in the hook.
    /// @param instructionLength Amount of bytes indicating the size of the instruction(s) that will be overwritten by the hook. Must be 5 or greater.
    /// @return BOOL: Whether or not the hook could be created.
    static BOOL CreateHook(DWORD toHookLocation, void* hookAddr, int instructionLength);
};
