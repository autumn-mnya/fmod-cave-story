#include <Windows.h>
// Filesystem
#include <iostream>
#include <filesystem>
#include <stddef.h>
#include <cstdio>
#include <stdlib.h>
#include <string>

#include <fmod_studio.hpp>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <fmod_common.h>

#include "Main.h"
#include "mod_loader.h"
#include "cave_story.h"
#include "TextScript.h"

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
FMOD_GUID guid;

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

	// Initialize FMOD Studio, which will also initialize FMOD Core
	result = FmodStudioObj->initialize(1024, FMOD_STUDIO_INIT_SYNCHRONOUS_UPDATE, FMOD_INIT_NORMAL, extraDriverData);
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
}

void fmod_LoadBanks()
{
	char path[MAX_PATH];
	
	sprintf(path, "%s\\%s", gAudioPath, gNullPath);

	for (const auto& entry : std::filesystem::directory_iterator(path))
		FmodStudioObj->loadBankFile(entry.path().string().c_str(), FMOD_STUDIO_LOAD_BANK_NORMAL, &FmodBankObj);
}

void fmod_ParseGuidsTXT()
{
	FILE* fp;
	char path[MAX_PATH];

	char line[256];

	sprintf(path, "%s\\%s", GUIDsPath, gNullPath);
	
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		fp = fopen(entry.path().string().c_str(), "rb");

		while (fgets(line, sizeof(line), fp)) {
			char* end = strchr(line, ' ');
			if (end) {
				*end = '\0';
			}
			sscanf(line, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
				&guid.Data1, &guid.Data2, &guid.Data3,
				&guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
				&guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);
			// Do something with the GUID
			FMOD::Studio::parseID(line, &guid);
		}
	}
}

// Replease Fmod Audio
void ReleaseFmod()
{
	FmodBankObj->unload();
	FmodStudioObj->release();
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

void StopFmodAllAudio()
{
	FmodMusicInstance->release();
	PlayAudio(gNull1Name);
	PlayAudio(gNull2Name);
	PlayAudio(gNull3Name);
	PlayAudio(gNull4Name);
	PlayAudio(gNull5Name);
	PlayAudio(gNull6Name);
	PlayAudio(gNull7Name);
	PlayAudio(gNull8Name);
}