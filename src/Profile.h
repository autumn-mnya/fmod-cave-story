#pragma once

#include <Windows.h>

#include "cave_story.h"

extern const char* gFmodFileName;

typedef struct ProfileFmodData
{
	char eventName[MAX_PATH];
	char eventName2[MAX_PATH];
	char eventName3[MAX_PATH];
	char eventName4[MAX_PATH];
	char eventName5[MAX_PATH];
	char eventName6[MAX_PATH];
	char eventName7[MAX_PATH];
	char eventName8[MAX_PATH];
} ProfileFmodData;

void Replacement_TextScript_SaveProfile_Call(const char* name);
void Replacement_LoadProfile_ClearValueView_Call();
void FModClearEventNames();