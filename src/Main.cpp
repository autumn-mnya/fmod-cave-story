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
#include "Npc.h"
#include "Game.h"
#include "Profile.h"
#include "TextScript.h"

#include "AutPI.h"
#include "lua/Lua.h"

// Paths
char gModulePath[MAX_PATH];
char gDataPath[MAX_PATH];
char gAudioPath[MAX_PATH];

const char* audioDirectory = "data\\audio\\Desktop";

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
	strcat(gAudioPath, "\\");
	strcat(gAudioPath, audioDirectory);
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
	// Dont pause the window
	ModLoader_WriteByte((void*)0x413593, 0x71);
	ModLoader_WriteByte((void*)0x412BC0, 0xC3);
	ModLoader_WriteByte((void*)0x412BF0, 0xC3);

	InitMod_ReplacementChangeMusic();
	RegisterInitializeGameInitElement(FModClearEventNames);
	// Game
	RegisterGetTrgElement(FModUpdate);
	RegisterReleaseElement(ReleaseFModAudio);

	if (replace_npc_code)
	{
		ModLoader_WriteJump((void*)0x43AAF0, (void*)Replacement_ActNpc096);
		ModLoader_WriteJump((void*)0x43AD10, (void*)Replacement_ActNpc097);
		ModLoader_WriteJump((void*)0x43AF20, (void*)Replacement_ActNpc098);
		ModLoader_WriteJump((void*)0x43B140, (void*)Replacement_ActNpc099);
	}

	// Profile
	ModLoader_WriteCall((void*)0x41D52B, (void*)Replacement_LoadProfile_ClearValueView_Call);
}

void InitMod(void)
{
	LoadAutPiDll();
	InitMod_Settings();
	GetGamePath();
	fmod_Init();
	fmod_LoadBanks();
	InitReplacements();
	InitMod_TSC();

	RegisterSVPElement(SaveFModCall);

	RegisterLuaPreGlobalModCSElement(SetFMODGlobalString);
	RegisterLuaFuncElement(SetFMODLua);
}
