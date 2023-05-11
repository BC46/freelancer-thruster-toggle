#include "hooks.h"

DWORD   thrustToggleReturnAddress,
        checkThrusterReturnAddress,
        loadSceneReturnAddress,
        keyCmdNicknameCheckReturnAddress,
        playerThrustAddress,
        jmpFtolAddress,
        idsNameReturnAddress,
        keyUpStateReturnAddress,
        iniReaderGetValueStringAddress,
        stricmpAddress;

long newIdsName;

BYTE isThrustOn = 0;
BYTE hasBeenActivated = 0;
BYTE foundAfterburnNickname = 0;
BYTE keymapEditsComplete = 0;

const char *afterburnNickname = "USER_AFTERBURN";

void __declspec(naked) ThrustToggleHook()
{
    __asm {
        mov     edx, dword ptr ds:[eax]             // Overwritten instruction
        xor     ecx, ecx
        cmp     byte ptr [hasBeenActivated], 1      // Check if the thruster has been activated
        je      toggleThrust
        mov     byte ptr [isThrustOn], 1            // Indicate that the thruster is on if it wasn't already
        add     cl, 1                               // Activate the thruster
        jmp     done

    toggleThrust:
        push    eax                                 // Save register values
        push    ebx
        mov     bl, byte ptr [isThrustOn]
        test    bl, bl                              // Test whether the thruster was on previously
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

void __declspec(naked) CheckThrusterHook()
{
    __asm {
        mov     eax, dword ptr ss:[esp+4]           // Overwritten instructions
        push    ebx
        mov     esi, playerThrustAddress
        cmp     esi, ss:[esp+4]                     // Check if the player is using the thruster
        jne     done                                // Ignore if the function is called by an NPC
        mov     byte ptr [hasBeenActivated], al     // Set thruster as activated/deactivated accordingly

    done:
        jmp     [checkThrusterReturnAddress]        // Go back to the original code
    }
}

void __declspec(naked) DisableThrusterHook()
{
    __asm {
        mov     esi, dword ptr ss:[esp+0xC]         // Overwritten instructions
        push    edi
        mov     byte ptr [isThrustOn], 0            // Disable the thruster
        mov     byte ptr [hasBeenActivated], 0
        jmp     [loadSceneReturnAddress]            // Go back to the original code
    }
}

void __declspec(naked) UserAfterburnKeyCmdNicknameHook()
{
    __asm {
        call    dword ptr ds:[iniReaderGetValueStringAddress]   // Overwritten instruction
        cmp     byte ptr [keymapEditsComplete], 1
        je      done                                            // Don't carry on if the edits have already been completed
        push    ecx                                             // Save register values
        push    edx
        push    eax                                             // Set value string from ini reader as parameter 2
        push    [afterburnNickname]                             // Set the afterburn nickname as parameter 1
        call    dword ptr [stricmpAddress]                      // Call stricmp
        test    al, al
        sete    byte ptr [foundAfterburnNickname]               // Set foundAfterburnNickname to 1 if the 2 strings are equal
        add     esp, 4
        pop     eax                                             // Restore saved register values
        pop     edx
        pop     ecx

    done:
        jmp     [keyCmdNicknameCheckReturnAddress]              // Go back to the original code
    }
}

void __declspec(naked) UpdateIdsNameHook()
{
    __asm {
        call    dword ptr ds:[jmpFtolAddress]           // Overwritten instruction
        cmp     byte ptr [keymapEditsComplete], 1
        je      done                                    // Don't carry on if the edits have already been completed
        cmp     byte ptr [foundAfterburnNickname], 0
        cmovne  eax, dword ptr [newIdsName]             // Replace the ids name if the afterburn nickname has been found

    done:
        jmp     [idsNameReturnAddress]                  // Go back to the original code
    }
}

void __declspec(naked) RemoveKeyUpStateHook()
{
    __asm {
        add     esp, 8                                  // Overwritten instruction #1
        cmp     byte ptr [keymapEditsComplete], 1
        je      done                                    // Don't carry on if the edits have already been completed
        push    ecx
        mov     ecx, 1
        cmp     byte ptr [foundAfterburnNickname], 1    // If the nickname has been found...
        cmove   eax, ecx                                //      ensure the key up state won't be set after going back to the original code;
        sete    byte ptr [keymapEditsComplete]          //      set edits as complete
        pop     ecx

    done:
        test    eax, eax                                // Overwritten instruction #2
        jmp     [keyUpStateReturnAddress]               // Go back to the original code
    }
}
