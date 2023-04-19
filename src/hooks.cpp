#include "hooks.h"

DWORD thrustToggleReturnAddress;

BOOL isThrustOn;

void __declspec(naked) ThrustToggle() {
    __asm {
        mov     ecx, dword ptr ss:[esp+4]
        mov     edx, dword ptr ds:[eax]
        jmp     [thrustToggleReturnAddress]
    }
}
