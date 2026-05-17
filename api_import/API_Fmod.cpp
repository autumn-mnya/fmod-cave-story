#include <windows.h>
#include <iostream>
#include "API_Fmod.h"
#include "mod_loader.h"
#include "cave_story.h"

HMODULE fmodDLL = nullptr;

void LoadFmodDll()
{
    fmodDLL = LoadLibrary("fmodcs.dll");
    if (fmodDLL == nullptr) {
        std::cerr << "Failed to load fmodcs.dll\n";
        // You might want to handle the error appropriately, e.g., throw an exception or return early.
    }
}

void PlayFModAudio(const char* audiofile)
{
    typedef void (*funcdef)(const char*);

    funcdef func = reinterpret_cast<funcdef>(
        GetProcAddress(fmodDLL, "PlayFModAudio"));

    if (func == nullptr) {
        std::cerr << "Failed to get the function pointer for PlayFModAudio\n";
        return;
    }

    func(audiofile);
}

void StopFmodAllAudio()
{
    typedef void (*funcdef)();

    funcdef func = reinterpret_cast<funcdef>(
        GetProcAddress(fmodDLL, "StopFmodAllAudio"));

    if (func == nullptr) {
        std::cerr << "Failed to get the function pointer for StopFmodAllAudio\n";
        return;
    }

    func();
}

void FModClearEventNames()
{
    typedef void (*funcdef)();

    funcdef func = reinterpret_cast<funcdef>(
        GetProcAddress(fmodDLL, "FModClearEventNames"));

    if (func == nullptr) {
        std::cerr << "Failed to get the function pointer for FModClearEventNames\n";
        return;
    }

    func();
}

void FModUpdate()
{
    typedef void (*funcdef)();

    funcdef func = reinterpret_cast<funcdef>(
        GetProcAddress(fmodDLL, "FModUpdate"));

    if (func == nullptr) {
        std::cerr << "Failed to get the function pointer for FModUpdate\n";
        return;
    }

    func();
}