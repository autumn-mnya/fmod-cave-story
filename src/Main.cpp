#include <Windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_common.h>

#include "Main.h"
#include "mod_loader.h"
#include "cave_story.h"
#include "fmodAudio.h"
#include "TextScript.h"

// Paths
char gModulePath[MAX_PATH];
char gDataPath[MAX_PATH];
char gAudioPath[MAX_PATH];

void GetGamePath()
{
	// Get executable's path
	GetModuleFileNameA(NULL, gModulePath, MAX_PATH);
	PathRemoveFileSpecA(gModulePath);

	// Get path of the data folder
	strcpy(gDataPath, gModulePath);
	strcat(gDataPath, "\\data");

	// Get path of the audio folder
	strcpy(gAudioPath, gModulePath);
	strcat(gAudioPath, "\\audio\\Desktop");
}

// 0x412BD6
void Replacement_InactiveWindow_StopOrganya_Call()
{
	FmodMusicInstance->setPaused(true);
	StopOrganyaMusic();
	printf("try to pause the music lol\n");
}

void Replacement_ActiveWindow_StopOrganya_Call()
{
	StopOrganyaMusic();
	printf("try to play the music lol\n");
	FmodMusicInstance->setPaused(false);
}

void Replacement_ModeOpening_ActNpChar_Call()
{
	/*
	bool is_playing = false;

	if (is_playing == false)
	{
		PlayAudio("event:/Doukutsu/GoldenHour");
		is_playing = true;
	}
	*/

	// Update audio
	FmodStudioObj->update();

	ActNpChar();
}

void Replacement_ModeTitle_ActCaret_Call()
{
	FmodStudioObj->update();
	ActCaret();
}

void Replacement_ModeAction_ActStar_Call()
{
	FmodStudioObj->update();
	ActStar();
}

void ReleaseFmod()
{
	FmodBankObj->unload();
	FmodStringsBankObj->unload();
	FmodStudioObj->release();
}

void ReleaseCreditReplacement()
{
	ReleaseCreditScript();
	ReleaseFmod();
}

void InitReplacements()
{
	// ModLoader_WriteJump((void*)0x412BC0, (void*)Replacement_InactiveWindow);
	ModLoader_WriteCall((void*)0x412BD6, (void*)Replacement_InactiveWindow_StopOrganya_Call);
	ModLoader_WriteCall((void*)0x412C06, (void*)Replacement_ActiveWindow_StopOrganya_Call);
	ModLoader_WriteCall((void*)0x40F809, (void*)Replacement_ModeOpening_ActNpChar_Call);
	ModLoader_WriteCall((void*)0x40FFDC, (void*)Replacement_ModeTitle_ActCaret_Call);
	ModLoader_WriteCall((void*)0x410555, (void*)Replacement_ModeAction_ActStar_Call);
	ModLoader_WriteCall((void*)0x40F6F9, (void*)ReleaseCreditReplacement);
}

void InitMod(void)
{
	GetGamePath();
	fmod_Init();
	fmod_LoadBanks();
	InitReplacements();
	InitMod_TSC();
}
