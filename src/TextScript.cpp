#include <Windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "TextScript.h"

#include "main.h"

#include "mod_loader.h"
#include "mod_loader_hooks.h"
#include "cave_story.h"
#include "fmodAudio.h"

char eventName[MAX_PATH];

// Used for playing fmod audio files
void GetTextScriptString(char returnData[])
{
	int i = 0;
	while (gTS->data[gTS->p_read] != '$') {
		returnData[i] = gTS->data[gTS->p_read];
		gTS->p_read++;
		i++;
	}
	//Insert the null terminator overtop the $
	returnData[i] = '\0';
	//Skip over the '$'
	gTS->p_read++;
}

static int CustomTextScriptCommands(MLHookCPURegisters* regs, void* ud)
{
	(void)ud;
	int w, x, y, z;

	char* where = TextScriptBuffer + gTS->p_read;
	if (where[0] != '<')
		return 0;
	if (strncmp(where + 1, "PEV", 3) == 0)
	{
		gTS->p_read += 4;
		GetTextScriptString(eventName);
		PlayAudio(eventName);
	}
	else if (strncmp(where + 1, "SEV", 3) == 0)
	{
		gTS->p_read += 4;
		// I should set eventName to 0 or something ..
		// Would help with saving/loading a profile I would assume?
		FmodMusicInstance->release();
		FmodMusicInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE);
	}
	else
		return 0;

	regs->eip = CSJ_tsc_done;
	return 1;
}

void InitMod_TSC()
{
	ModLoader_AddStackableHook(CSH_tsc_start, CustomTextScriptCommands, (void*)0);
}