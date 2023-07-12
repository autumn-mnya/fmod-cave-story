#include <Windows.h>
// Filesystem
#include <iostream>
#include <filesystem>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_common.h>

#include "Main.h"
#include "mod_loader.h"
#include "cave_story.h"
namespace fs = std::filesystem;

const char* gBankName = "Master.bank";
const char* gStringsBankName = "Master.strings.bank";
const char* gNullPath = "";

// Fmod objects
FMOD_RESULT result;
FMOD::Studio::System* FmodStudioObj;
FMOD::Studio::Bank* FmodBankObj;
FMOD::Studio::EventDescription* FmodEventDescription;
FMOD::Studio::EventInstance* FmodMusicInstance; // Music Instance
FMOD::Studio::Bus* FmodEventBus; // Event Bus (Non Functional)
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
	char path[MAX_PATH];
	
	sprintf(path, "%s\\%s", gAudioPath, gNullPath); // gNullPath is needed for some unknown reason. This is like the fucking tf2 object

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		FmodStudioObj->loadBankFile(entry.path().string().c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &FmodBankObj); // this genuinely might just go lmao
	}

	printf("FMOD Banks Loaded");
}

void PlayAudio(const char* audiofile)
{
	// Load audio
	FMOD::Studio::EventDescription* eventDescription = NULL;
	FmodStudioObj->getEvent(audiofile, &eventDescription);

	// Create audio
	FmodMusicInstance = NULL;
	eventDescription->createInstance(&FmodMusicInstance);

	// Start audio
	FmodMusicInstance->start();

	// Release when finished(?)
	FmodMusicInstance->release();
}