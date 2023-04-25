#pragma once

#include <vector>
#include <windows.h>

struct HookInfo {
    DWORD toHookLocation;
    void* hookAddr;
    int instructionLength;
};

class HookManager {
private:
    /// @brief Registered hooks.
    std::vector<HookInfo> hooks;

    /// @brief Registers a hook with the given info.
    /// @param hookInfo
    /// @return Return address of the hook.
    DWORD RegisterHookInternal(HookInfo &hookInfo);

public:
    /// @brief Registers a hook in the main module.
    /// @param fileOffset File offset in the main module where the hook should be set.
    /// @param hookAddr Address of the function that should be called in the hook.
    /// @param instructionLength Amount of bytes indicating the size of the instruction(s) that will be overwritten by the hook. Must be 5 or greater.
    /// @return Return address of the hook.
    DWORD RegisterMainHook(DWORD fileOffset, void* hookAddr, int instructionLength);

    /// @brief Registers a hook in a specific module.
    /// @param moduleName Name of the module where the hook should be set.
    /// @param fileOffset File offset in the given module where the hook should be set.
    /// @param hookAddr Address of the function that should be called in the hook.
    /// @param instructionLength Amount of bytes indicating the size of the instruction(s) that will be overwritten by the hook. Must be 5 or greater.
    /// @return Return address of the hook.
    DWORD RegisterModuleHook(const std::string &moduleName, DWORD fileOffset, void* hookAddr, int instructionLength);

    /// @brief Sets/creates all the registered hooks.
    /// @return Whether or not all hooks have been created successfully.
    BOOL InitializeHooks();
};
