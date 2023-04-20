#include "hooks.h"

DWORD thrustToggleReturnAddress;
DWORD checkThrusterReturnAddress;
DWORD playerThrustAddress;

BYTE isThrustOn = 0;
BYTE hasBeenActivated = 0;

void __declspec(naked) ThrustToggle() {
    __asm {
        mov     edx, dword ptr ds:[eax]             // Overwritten instruction
        xor     ecx, ecx
        cmp     byte ptr [hasBeenActivated], 1      // Check if the thruster has been activated
        je      toggleThrust
        mov     byte ptr [isThrustOn], 1
        add     cl, 1                               // Activate the thruster
        jmp     done
    toggleThrust:
        push    eax                                 // Save register values
        push    ebx
        mov     bl, byte ptr [isThrustOn]
        test    bl, bl                              // Test wether the thruster was on previously
        jnz     restore
        xor     byte ptr [isThrustOn], 1            // Toggle the thrust state
        mov     al, byte ptr [isThrustOn]
        test    al, al
        setne   cl                                  // Activate/deactivate the thruster based on the toggled value
    restore:
        pop     ebx                                 // Restore saved register values
        pop     eax
    done:
        mov     byte ptr [hasBeenActivated], 0      // Reset the activated value
        jmp     [thrustToggleReturnAddress]         // Go back to the original code
    }
}

void __declspec(naked) CheckThruster()
{
    __asm {
        mov     eax, dword ptr ss:[esp+4]           // Overwritten instructions
        push    ebx
        mov     esi, playerThrustAddress
        cmp     esi, ss:[esp+4]                     // Check if the player is using the thruster
        jne     done                                // Ignore if the function is called by an NPC
        mov     byte ptr [hasBeenActivated], al     // Set thruster as activated
    done:
        jmp     [checkThrusterReturnAddress]        // Go back to the original code
    }
}
