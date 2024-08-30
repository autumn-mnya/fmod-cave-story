#pragma once

#include <Windows.h>
#include "cave_story.h"
#include <vector>

extern HMODULE fmodDLL;  // Global variable

void LoadFmodDll();
void PlayFModAudio(const char* audiofile);
void StopFmodAllAudio();
void FModClearEventNames();
void FModUpdate();