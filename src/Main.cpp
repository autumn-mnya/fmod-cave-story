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


#include "mod_loader.h"
#include "cave_story.h"

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

const char* gBankName = "Doukutsu.bank";
const char* gStringsBankName = "Doukutsu.strings.bank";

// Fmod objects
FMOD_RESULT result;
FMOD::Studio::System* FmodStudioObj;
FMOD::Studio::Bank* FmodBankObj;
FMOD::Studio::Bank* FmodStringsBankObj;
FMOD::Studio::EventDescription* FmodEventDescription;
FMOD::Studio::EventInstance* FmodEventInstance;
FMOD::Studio::Bus* FmodEventBus;
FMOD::System* coreSystem;

void Common_Init(void** /*extraDriverData*/)
{
	CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
}

void fmod_Init()
{
	void* extraDriverData = NULL;
	Common_Init(&extraDriverData);

	result = FMOD::Studio::System::create(&FmodStudioObj); // Create the Studio System object.

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
	result = FmodStudioObj->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);
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
	char path_MasterBank[MAX_PATH];
	char path_StringsBank[MAX_PATH];
	sprintf(path_MasterBank, "%s\\%s", gAudioPath, gBankName);
	sprintf(path_StringsBank, "%s\\%s", gAudioPath, gStringsBankName);

	FmodStudioObj->loadBankFile(path_MasterBank, FMOD_STUDIO_LOAD_BANK_NORMAL, &FmodBankObj);
	FmodStudioObj->loadBankFile(path_StringsBank, FMOD_STUDIO_LOAD_BANK_NORMAL, &FmodStringsBankObj);

	printf("FMOD Banks Loaded");
}

void Replacement_ModeOpening_ActNpChar_Call()
{
	// Load audio
	FMOD::Studio::EventDescription* eventDescription = NULL;
	FmodStudioObj->getEvent("event:/Doukutsu/GoldenHour", &eventDescription);

	// Create audio
	FMOD::Studio::EventInstance* eventInstance = NULL;
	eventDescription->createInstance(&eventInstance);

	// Start audio
	eventInstance->start();

	// Release when finished(?)
	eventInstance->release();

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

void InitReplacements()
{
	ModLoader_WriteCall((void*)0x40F809, (void*)Replacement_ModeOpening_ActNpChar_Call);
	ModLoader_WriteCall((void*)0x40FFDC, (void*)Replacement_ModeTitle_ActCaret_Call);
	ModLoader_WriteCall((void*)0x410555, (void*)Replacement_ModeAction_ActStar_Call);
}

void InitMod(void)
{
	GetGamePath();
	fmod_Init();
	fmod_LoadBanks();
	InitReplacements();
}
