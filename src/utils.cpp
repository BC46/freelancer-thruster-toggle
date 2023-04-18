#include "utils.h"

BOOL Utils::Hook(void* toHookLocation, void* hookAddr, int instructionLength) {
    // The length of the instruction needs to be at least 5 bytes in order to change it to a jump
    if (instructionLength < 5)
        return false;
    
    // Allows the instruction to be overwritten
    DWORD oldProtection, _;
    VirtualProtect(toHookLocation, instructionLength, PAGE_EXECUTE_READWRITE, &oldProtection);
    
    // Change any remaining bytes to "nop" to prevent them from potentially causing issues
    if (instructionLength > 5)
        memset(((char *) toHookLocation + 5), 0x90, instructionLength - 5);
    
    // Calculate the relative jump address to the hook function
    DWORD jumpAddress = (DWORD) hookAddr - (DWORD) toHookLocation - 5;
    
    // Write the instruction that jumps to the hook function
    *(BYTE*) toHookLocation = 0xE9;
    memcpy((DWORD *) toHookLocation + 1, &jumpAddress, sizeof(DWORD));
    
    // Revert protection changes
    VirtualProtect(toHookLocation, instructionLength, oldProtection, &_);
    
    return true;
}