#include <Windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Game.h"

#include "main.h"

#include "mod_loader.h"
#include "mod_loader_hooks.h"
#include "cave_story.h"
#include "fmodAudio.h"
#include "TextScript.h"

const char* setting_titlescreen_cavestory_music = gNull1Name;
const char* setting_titlescreen_hell_music = gNull1Name;
const char* setting_titlescreen_toroko_music = gNull1Name;
const char* setting_titlescreen_white_music = gNull1Name;
const char* setting_titlescreen_safety_music = gNull1Name;

void Replacement_ModeOpening_ChangeMusic_Silence_Call(MusicID no)
{
	ChangeMusic(no);
	StopFmodAllAudio();
}

void Replacement_ModeTitle_ChangeMusic_RunningHell_Call(MusicID no)
{
	ChangeMusic(no);
	PlayAudio(setting_titlescreen_hell_music);
}

void Replacement_ModeTitle_ChangeMusic_TorokosTheme_Call(MusicID no)
{
	ChangeMusic(no);
	PlayAudio(setting_titlescreen_toroko_music);
}

void Replacement_ModeTitle_ChangeMusic_White_Call(MusicID no)
{
	ChangeMusic(no);
	PlayAudio(setting_titlescreen_white_music);
}

void Replacement_ModeTitle_ChangeMusic_Safety_Call(MusicID no)
{
	ChangeMusic(no);
	PlayAudio(setting_titlescreen_safety_music);
}

void Replacement_ModeTitle_ChangeMusic_CaveStory_Call(MusicID no)
{
	ChangeMusic(no);
	PlayAudio(setting_titlescreen_cavestory_music);
}

void Replacement_ModeTitle_ChangeMusic_Silence_Call(MusicID no)
{
	// fmod audio stops getting updated outside of the loop, so we update it once the music is supposed to be stopped
	ChangeMusic(no);
	StopFmodAllAudio();
	FmodStudioObj->update();
}