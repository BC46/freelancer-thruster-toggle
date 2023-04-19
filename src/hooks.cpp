#include "hooks.h"

DWORD thrustToggleReturnAddress;

BYTE isThrustOn;

void __declspec(naked) ThrustToggle() {
    __asm {
        mov     edx, dword ptr ds:[eax]
        push    eax
        push    ebx
        xor     byte ptr [isThrustOn], 1
        xor     ecx, ecx
        mov     al, byte ptr [isThrustOn]
        test    al, al
        setne   cl
        pop     ebx
        pop     eax
        jmp     [thrustToggleReturnAddress]
    }
}
