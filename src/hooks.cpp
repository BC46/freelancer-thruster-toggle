#include "hooks.h"

DWORD thrustToggleReturnAddress;

BYTE isThrustOn = 0;
BYTE hasBeenActivated = 0;

void __declspec(naked) ThrustToggle() {
    __asm {
        mov     edx, dword ptr ds:[eax]             // Overwritten instruction
        xor     ecx, ecx
        cmp     byte ptr [hasBeenActivated], 1
        je      toggleThrust
        mov     byte ptr [isThrustOn], 1
        add     cl, 1
        jmp     done

    toggleThrust:
        push    eax                                 // Save register values
        push    ebx
        xor     byte ptr [isThrustOn], 1
        mov     al, byte ptr [isThrustOn]
        test    al, al
        setne   cl
        pop     ebx                                 // Restore saved register values
        pop     eax

    done:
        mov     byte ptr [hasBeenActivated], 0
        jmp     [thrustToggleReturnAddress]
    }
}

void __declspec(naked) CheckThruster()
{
    __asm {
        mov     byte ptr [hasBeenActivated], 1      // Set thruster as activated
        mov     al, bl                              // Overwritten instructions
        pop     ebx
        ret     4
    }
}
