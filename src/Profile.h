#pragma once

#include <Windows.h>

#include "cave_story.h"

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

void SaveFmodFile();
void LoadFmodFile();
void FmodLoadProfileInit();