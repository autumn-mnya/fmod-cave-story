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

const char* gBankName = "Doukutsu.bank";
const char* gStringsBankName = "Doukutsu.strings.bank";

// Fmod objects
FMOD_RESULT result;
FMOD::Studio::System* FmodStudioObj;
FMOD::Studio::Bank* FmodBankObj;
FMOD::Studio::Bank* FmodStringsBankObj;
FMOD::Studio::EventDescription* FmodEventDescription;
FMOD::Studio::EventInstance* FmodMusicInstance; // Music
FMOD::Studio::Bus* FmodEventBus;
FMOD::System* coreSystem;

void ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		printf("FMOD error %d - %s", result, FMOD_ErrorString(result));
	}
}

void Common_Init(void** /*extraDriverData*/)
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
}

void fmod_Init()
{
	void* extraDriverData = NULL;
	Common_Init(&extraDriverData);

	FmodStudioObj = NULL;
	result = FmodStudioObj->create(&FmodStudioObj); // Create the Studio System object.

	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	// The Studio project is authored for Stereo sound, so set up the system output mode to match
	coreSystem = NULL;
	FmodStudioObj->getCoreSystem(&coreSystem);
	coreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0);

	if (result == FMOD_OK)
		printf("FMOD success! (%d) %s\n", result, FMOD_ErrorString(result));

	// Initialize FMOD Studio, which will also initialize FMOD Core
	result = FmodStudioObj->initialize(1024, FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE, FMOD_INIT_NORMAL, extraDriverData);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	if (result == FMOD_OK)
		printf("FMOD success! (%d) %s\n", result, FMOD_ErrorString(result));
}

void fmod_LoadBanks()
{
	// Load bank files
	char path_MasterBank[MAX_PATH];
	char path_StringsBank[MAX_PATH];
	sprintf(path_MasterBank, "%s\\%s", gAudioPath, gBankName);
	sprintf(path_StringsBank, "%s\\%s", gAudioPath, gStringsBankName);

	FmodStudioObj->loadBankFile(path_MasterBank, FMOD_STUDIO_LOAD_BANK_NORMAL, &FmodBankObj);
	FmodStudioObj->loadBankFile(path_StringsBank, FMOD_STUDIO_LOAD_BANK_NORMAL, &FmodStringsBankObj);

	printf("FMOD Banks Loaded");
}

void PlayAudio(const char* audiofile)
{
	// Load audio
	FMOD::Studio::EventDescription* eventDescription = NULL;
	ERRCHECK(FmodStudioObj->getEvent(audiofile, &eventDescription));

	// Create audio
	FmodMusicInstance = NULL;
	ERRCHECK(eventDescription->createInstance(&FmodMusicInstance));

	// Start audio
	ERRCHECK(FmodMusicInstance->start());

	// Release when finished(?)
	ERRCHECK(FmodMusicInstance->release());
}