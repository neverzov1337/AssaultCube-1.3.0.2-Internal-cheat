// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <Minhook.h>
#include "imgui\imgui.h"
#include "imgui\imgui_impl_win32.h"
#include "imgui\imgui_impl_opengl2.h"

typedef int(__cdecl* Print)(const char* a1, const char* text, ...);
Print print_text = (Print)0x4DAD50;
Print print_original = nullptr;
DWORD ModuleBase = (DWORD)GetModuleHandle("ac_client.exe");
uintptr_t* localplayer = (uintptr_t*)(ModuleBase + 0x17E0A8);
uintptr_t doDamageAddr = 0x429C20;

bool isRapid;
bool isHealth;
bool isArmor;
bool isAmmo;
bool isGod;

int __cdecl HookedPrint(const char* a1, const char* text, ...) {
    if (strcmp(text, "health") == 0) {
        isHealth = !isHealth;
        return print_original("Inf health has been enabled", "", "");
    }
    if (strcmp(text, "rapid") == 0) {
        isRapid = !isRapid;
        return print_original("Rapid has been enabled", "", "");
    }
    if (strcmp(text, "armor") == 0) {
        isArmor = !isArmor;
        return print_original("Inf armor has been enabled", "", "");
    }
    if (strcmp(text, "ammo") == 0) {
        isAmmo = !isAmmo;
        return print_original("Inf ammo has been enabled", "", "");
    }
    if (strcmp(text, "godmode") == 0) {
        isGod = !isGod;
        return print_original("You is God", "", "");
    }
    return print_original(a1, text);
}

typedef void(__fastcall* tDoDamage)(void* targetPlayer, void* edx, int damage, void* actorPlayer);
tDoDamage oDoDamage = nullptr;

//void __fastcall HookedDoDamage(void* targetPlayer, void* edx, int damage, void* actorPlayer) {
//    if (localplayer != nullptr && *localplayer != 0 && (uintptr_t)targetPlayer == *localplayer && isGod) {
//        return;
//    }
//
//    oDoDamage(targetPlayer, edx, damage, actorPlayer);
//}
 
DWORD WINAPI MainThread(HMODULE hModule) 
{
    MH_Initialize();
    MH_CreateHook((LPVOID)0x4DAD50, &HookedPrint, reinterpret_cast<LPVOID*>(&print_original));
    MH_EnableHook((LPVOID)0x4DAD50);
    //MH_CreateHook((LPVOID)doDamageAddr, &HookedDoDamage, reinterpret_cast<LPVOID*>(&oDoDamage));
    //MH_EnableHook((LPVOID)doDamageAddr);
    while (true) {
        if (isRapid == true) {
                *(int*)(*localplayer + 0x158) = 0;
                *(int*)(*localplayer + 0x160) = 0;
                *(int*)(*localplayer + 0x164) = 0;
        }
        if (isHealth) {
            int* health = (int*)(*localplayer + 0xEC);
            *health = 1337;
        }
        if (isArmor) {
            int* armor = (int*)(*localplayer + 0xF0);
            *armor = 1337;
        }
        if (isAmmo) {
            *(int*)(*localplayer + 0x12C) = 1337;
            *(int*)(*localplayer + 0x130) = 1337;
            *(int*)(*localplayer + 0x134) = 1337;
            *(int*)(*localplayer + 0x138) = 1337;
            *(int*)(*localplayer + 0x13C) = 1337;
            *(int*)(*localplayer + 0x140) = 1337;
            *(int*)(*localplayer + 0x144) = 1337;
        }
        Sleep(5);
    }
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

