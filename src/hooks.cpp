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
        cmp     byte ptr [hasBeenActivated], 1
        je      toggleThrust
        mov     byte ptr [isThrustOn], 1
        add     cl, 1
        jmp     done

    toggleThrust:
        push    eax                                 // Save register values
        push    ebx
        mov     bl, byte ptr [isThrustOn]
        test    bl, bl
        jnz     restore
        xor     byte ptr [isThrustOn], 1
        mov     al, byte ptr [isThrustOn]
        test    al, al
        setne   cl

    restore:
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
        mov     eax, dword ptr ss:[esp+4]           // Overwritten instructions
        push    ebx
        mov     esi, playerThrustAddress
        cmp     esi, ss:[esp+4]
        jne     done
        mov     byte ptr [hasBeenActivated], al     // Set thruster as activated

    done:
        jmp     [checkThrusterReturnAddress]
    }
}
