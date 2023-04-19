#include "utils.h"

std::map<std::string, HMODULE> Utils::modules;

void* Utils::GetVirtualOffset(const std::string &module, DWORD fileOffset)
{
    DWORD moduleOffset = (DWORD) FindModuleHandle(module);

    return reinterpret_cast<void*>(moduleOffset + fileOffset);
}

void* Utils::GetProcOffset(const std::string &module, const std::string &proc)
{
    HMODULE moduleHandle = FindModuleHandle(module);
    FARPROC procAddress = GetProcAddress(moduleHandle, proc.c_str());

    return reinterpret_cast<void*>(procAddress);
}

HMODULE Utils::FindModuleHandle(const std::string &moduleName)
{
    // Try to find the module handle
    std::map<std::string, HMODULE>::iterator it = modules.find(moduleName.c_str());

    // If the module handle isn't stored in the cache yet, add it to the cache and return it
    if (it == modules.end()) {
        HMODULE handle = GetModuleHandleA(moduleName.c_str());

        modules.insert(std::pair<std::string, HMODULE>(moduleName, handle));
        return handle;
    }

    // Return the found module handle
    return it->second;
}

BOOL Utils::Hook(void* toHookLocation, void* hookAddr, int instructionLength)
{
    // The length of the instruction needs to be at least 5 bytes in order to change it to a jump
    if (instructionLength < 5)
        return false;

    // Allows the instruction to be overwritten
    DWORD oldProtection, _;
    VirtualProtect(toHookLocation, instructionLength, PAGE_READWRITE, &oldProtection);

    // Change any remaining bytes to "nop" to prevent them from potentially causing issues
    if (instructionLength > 5)
        memset(((char *) toHookLocation + 5), 0x90, instructionLength - 5);

    // Calculate the relative jump address to the hook function
    DWORD jumpAddress = (DWORD) hookAddr - (DWORD) toHookLocation - 5;

    // Write the instruction that jumps to the hook function
    *(BYTE*) toHookLocation = 0xE9;
    memcpy((void *) ((DWORD) toHookLocation + 1), &jumpAddress, sizeof(DWORD));

    // Revert protection changes
    VirtualProtect(toHookLocation, instructionLength, oldProtection, &_);

    return true;
}
