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
#include "ModSettings.h"
#include "mod_loader.h"
#include "cave_story.h"
#include "fmodAudio.h"
#include "Game.h"
#include "Profile.h"
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
	strcpy(gAudioPath, gDataPath);
	strcat(gAudioPath, "\\audio\\Desktop");
}

/*
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
*/

void Replacement_ModeOpening_ActNpChar_Call()
{
	// Update audio
	FmodStudioObj->update();

	ActNpChar();
}

void Replacement_ModeTitle_ActCaret_Call()
{
	// Update audio
	FmodStudioObj->update();

	ActCaret();
}

void Replacement_ModeAction_ActStar_Call()
{
	// Update audio
	FmodStudioObj->update();

	ActStar();
}

void ReleaseCreditReplacement()
{
	ReleaseCreditScript();
	ReleaseFmod();
}

void InitMod_ReplacementChangeMusic()
{
	ModLoader_WriteCall((void*)0x40F756, (void*)Replacement_ModeOpening_ChangeMusic_Silence_Call);
	ModLoader_WriteCall((void*)0x40FE81, (void*)Replacement_ModeTitle_ChangeMusic_RunningHell_Call);
	ModLoader_WriteCall((void*)0x40FE96, (void*)Replacement_ModeTitle_ChangeMusic_TorokosTheme_Call);
	ModLoader_WriteCall((void*)0x40FEAB, (void*)Replacement_ModeTitle_ChangeMusic_White_Call);
	ModLoader_WriteCall((void*)0x40FEC0, (void*)Replacement_ModeTitle_ChangeMusic_Safety_Call);
	ModLoader_WriteCall((void*)0x40FECC, (void*)Replacement_ModeTitle_ChangeMusic_CaveStory_Call);
	ModLoader_WriteCall((void*)0x41038C, (void*)Replacement_ModeTitle_ChangeMusic_Silence_Call);
}

void InitReplacements()
{
	// Main
	// Disable Inactive/Active stuff - lazy solution to not being able to pause audio
	ModLoader_WriteCall((void*)0x413316, (void*)ActiveWindow);

	/*
	ModLoader_WriteCall((void*)0x412BD6, (void*)Replacement_InactiveWindow_StopOrganya_Call);
	ModLoader_WriteCall((void*)0x412C06, (void*)Replacement_ActiveWindow_StopOrganya_Call);
	*/
	InitMod_ReplacementChangeMusic();
	// Game
	ModLoader_WriteCall((void*)0x40F809, (void*)Replacement_ModeOpening_ActNpChar_Call);
	ModLoader_WriteCall((void*)0x40FFDC, (void*)Replacement_ModeTitle_ActCaret_Call);
	ModLoader_WriteCall((void*)0x410555, (void*)Replacement_ModeAction_ActStar_Call);
	ModLoader_WriteCall((void*)0x40F6F9, (void*)ReleaseCreditReplacement);
	// Profile
	ModLoader_WriteCall((void*)0x424DAE, (void*)Replacement_TextScript_SaveProfile_Call);
	ModLoader_WriteCall((void*)0x41D52B, (void*)Replacement_LoadProfile_ClearValueView_Call);
}

void InitMod(void)
{
	GetGamePath();
	fmod_Init();
	fmod_LoadBanks();
	InitReplacements();
	InitMod_TSC();
	InitMod_Settings();
}
