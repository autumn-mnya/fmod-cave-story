#include <Windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Profile.h"

#include "main.h"

#include "AutPI.h"
#include "mod_loader.h"
#include "mod_loader_hooks.h"
#include "cave_story.h"
#include "fmodAudio.h"
#include "TextScript.h"

const char* gFmodFileName = "FMOD";

void SaveFmodFile()
{
	FILE* fp;
	ProfileFmodData profile;

	char path[MAX_PATH];

	// Get path
	sprintf(path, "%s\\%s.%s", gSavePath, GetCustomSaveName(), gFmodFileName);

	// Open file
	fp = fopen(path, "wb");
	if (fp == NULL)
		return;

	memset(&profile, 0, sizeof(ProfileFmodData));
	memcpy(profile.eventName, eventName, sizeof(profile.eventName));
	memcpy(profile.eventName2, eventName2, sizeof(profile.eventName2));
	memcpy(profile.eventName3, eventName3, sizeof(profile.eventName3));
	memcpy(profile.eventName4, eventName4, sizeof(profile.eventName4));
	memcpy(profile.eventName5, eventName5, sizeof(profile.eventName5));
	memcpy(profile.eventName6, eventName6, sizeof(profile.eventName6));
	memcpy(profile.eventName7, eventName7, sizeof(profile.eventName7));
	memcpy(profile.eventName8, eventName8, sizeof(profile.eventName8));

	// Write to file
	fwrite(&profile, sizeof(ProfileFmodData), 1, fp);

	fclose(fp);

	return;
}

void LoadFmodFile()
{
	FILE* fp;
	ProfileFmodData profile;
	char path[MAX_PATH];

	// Get path
	sprintf(path, "%s\\%s.%s", gSavePath, GetCustomSaveName(), gFmodFileName);

	// Open file
	fp = fopen(path, "rb");
	if (fp == NULL)
		return; // don't return false, but quit out early anyways

	// Read data
	fseek(fp, 0, SEEK_SET);
	memset(&profile, 0, sizeof(ProfileFmodData));
	fread(&profile, sizeof(ProfileFmodData), 1, fp);
	fclose(fp);

	// Set things
	memcpy(eventName, profile.eventName, sizeof(eventName));
	memcpy(eventName2, profile.eventName2, sizeof(eventName2));
	memcpy(eventName3, profile.eventName3, sizeof(eventName3));
	memcpy(eventName4, profile.eventName4, sizeof(eventName4));
	memcpy(eventName5, profile.eventName5, sizeof(eventName5));
	memcpy(eventName6, profile.eventName6, sizeof(eventName6));
	memcpy(eventName7, profile.eventName7, sizeof(eventName7));
	memcpy(eventName8, profile.eventName8, sizeof(eventName8));

	return;
}

void FmodLoadProfileInit()
{
	LoadFmodFile();
	
	// Play all fmod audio
	PlayFModAudio(eventName);
	PlayFModAudio(eventName2);
	PlayFModAudio(eventName3);
	PlayFModAudio(eventName4);
	PlayFModAudio(eventName5);
	PlayFModAudio(eventName6);
	PlayFModAudio(eventName7);
	PlayFModAudio(eventName8);
}