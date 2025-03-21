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
#include "Npc.h"
#include "Game.h"
#include "Profile.h"
#include "TextScript.h"

bool replace_npc_code = false;

void InitMod_Settings()
{
	audioDirectory = ModLoader_GetSettingString("FMOD Audio Directory", "data\\audio\\Desktop");

	setting_titlescreen_cavestory_music = ModLoader_GetSettingString("Title Screen Music (FMOD)", gNull1Name);
	setting_titlescreen_hell_music = ModLoader_GetSettingString("Title Screen Music [Running Hell] (FMOD)", gNull1Name);
	setting_titlescreen_toroko_music = ModLoader_GetSettingString("Title Screen Music [Torokos Theme] (FMOD)", gNull1Name);
	setting_titlescreen_white_music = ModLoader_GetSettingString("Title Screen Music [White] (FMOD)", gNull1Name);
	setting_titlescreen_safety_music = ModLoader_GetSettingString("Title Screen Music [Safety] (FMOD)", gNull1Name);

	replace_npc_code = ModLoader_GetSettingBool("Replace Fan Npc Code for Parameters", false);
}