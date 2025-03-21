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

bool fmodlogo_ready = false;
bool fmodlogo_done = false;
int tilesetsizeX = 256;
int tilesetsizeY = 256;
int tilesetSurface = 2;

// Paths
char gSavePath[MAX_PATH];
char gAudioPath[MAX_PATH];

const char* audioDirectory = "data\\audio\\Desktop";

void ReleaseFModBeforeGame()
{
	if (fmodlogo_done == false)
	{
		ReleaseSurface(tilesetSurface);
		MakeSurface_Generic(tilesetsizeX, tilesetsizeY, tilesetSurface, FALSE);
		fmodlogo_done = true;
	}
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
	RegisterLoadProfileInitElement(FmodLoadProfileInit);
}

// 0x411588
void LoadTilesetForFModLogo(int a, int b, int c, bool d)
{
	ReleaseSurface(c);
	MakeSurface_Generic(a, b, c, d);
	ReleaseSurface(c);
	tilesetsizeX = a;
	tilesetsizeY = b;
	tilesetSurface = c;
	MakeSurface_File("fmod-logo", tilesetSurface);
	fmodlogo_ready = true;
}

// 0x412AD2
void PutFModLogoWhenPossible(const RECT* a, int b, int c, const RECT* d, int e)
{
	MakeSurface_File("fmod-logo", tilesetSurface);
	fmodlogo_ready = true;

	RECT rcFmodLogo = { 0, 0, 132, 35 };
	PutBitmap3(a, b, c, d, e);
	if (fmodlogo_ready == true)
		PutBitmap3(a, (WINDOW_WIDTH / 2) - 66, (WINDOW_HEIGHT / 2) + 35, &rcFmodLogo, tilesetSurface);
}

void InitModPreMode()
{
	// Get path of the audio folder
	strcpy(gAudioPath, exeModulePath);
	strcat(gAudioPath, "\\");
	strcat(gAudioPath, audioDirectory);

	printf("%s\n", gAudioPath);

	strcpy(gSavePath, exeModulePath);
	strcat(gSavePath, "\\savedata");

	fmod_Init();
	fmod_LoadBanks();
	InitReplacements();
	InitMod_TSC();
}

void InitMod(void)
{
	LoadAutPiDll();
	InitMod_Settings();
	ModLoader_WriteCall((void*)0x412AD2, (void*)PutFModLogoWhenPossible);
	ModLoader_WriteCall((void*)0x411588, (void*)LoadTilesetForFModLogo);
	RegisterPreModeElement(InitModPreMode);
	RegisterInitElement(ReleaseFModBeforeGame);
	RegisterOpeningInitElement(ReleaseFModBeforeGame);
	RegisterTitleInitElement(ReleaseFModBeforeGame);
	RegisterSaveProfilePostCloseElement(SaveFmodFile);
	RegisterLuaPreGlobalModCSElement(SetFMODGlobalString);
	RegisterLuaFuncElement(SetFMODLua);
}
