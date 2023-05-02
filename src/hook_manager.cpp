#include "hook_manager.h"
#include "utils.h"

DWORD HookManager::RegisterHookInternal(HookInfo &hookInfo)
{
    hooks.push_back(hookInfo);

    return hookInfo.toHookLocation + hookInfo.instructionLength;
}

DWORD HookManager::RegisterMainHook(DWORD fileOffset, void *hookAddr, int instructionLength)
{
    DWORD toHookLocation = fileOffset + c_mainBase;
    HookInfo hookInfo = { toHookLocation, hookAddr, instructionLength };

    return RegisterHookInternal(hookInfo);
}

DWORD HookManager::RegisterModuleHook(const std::string &moduleName, DWORD fileOffset, void *hookAddr, int instructionLength)
{
    DWORD toHookLocation = Utils::GetVirtualOffset(moduleName, fileOffset);
    HookInfo hookInfo = { toHookLocation, hookAddr, instructionLength };

    return RegisterHookInternal(hookInfo);
}

BOOL HookManager::InitializeHooks()
{
    for (int i = 0; i < hooks.size(); ++i)
    {
        if (!Utils::CreateHook(hooks[i].toHookLocation, hooks[i].hookAddr, hooks[i].instructionLength))
            return FALSE;
    }

    return TRUE;
}
