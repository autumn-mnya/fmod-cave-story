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

int eventNameChoice = 0;

// Fmod Event Paths
const char* gNull1Name = "event:/Null/null0000";
const char* gNull2Name = "event:/Null/null0001";
const char* gNull3Name = "event:/Null/null0002";
const char* gNull4Name = "event:/Null/null0003";
const char* gNull5Name = "event:/Null/null0004";
const char* gNull6Name = "event:/Null/null0005";
const char* gNull7Name = "event:/Null/null0006";
const char* gNull8Name = "event:/Null/null0007";
const char* gNullParameter = "null";

char eventName[MAX_PATH] = "event:/Null/null0000";
char eventName2[MAX_PATH] = "event:/Null/null0001";
char eventName3[MAX_PATH] = "event:/Null/null0002";
char eventName4[MAX_PATH] = "event:/Null/null0003";
char eventName5[MAX_PATH] = "event:/Null/null0004";
char eventName6[MAX_PATH] = "event:/Null/null0005";
char eventName7[MAX_PATH] = "event:/Null/null0006";
char eventName8[MAX_PATH] = "event:/Null/null0007";
char eventParameter[MAX_PATH] = "null";

// Used for playing fmod audio files
// JakeV wrote this in "TSC Extended"
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
	if (strncmp(where + 1, "PEV", 3) == 0) // Play EVent
	{
		gTS->p_read += 4;

		switch (eventNameChoice)
		{
			default:
				memset(eventName, 0, sizeof(eventName));
				GetTextScriptString(eventName);
				PlayAudio(eventName);
				break;

			case 1:
				memset(eventName2, 0, sizeof(eventName2));
				GetTextScriptString(eventName2);
				PlayAudio(eventName2);
				break;

			case 2:
				memset(eventName3, 0, sizeof(eventName3));
				GetTextScriptString(eventName3);
				PlayAudio(eventName3);
				break;

			case 3:
				memset(eventName4, 0, sizeof(eventName4));
				GetTextScriptString(eventName4);
				PlayAudio(eventName4);
				break;

			case 4:
				memset(eventName5, 0, sizeof(eventName5));
				GetTextScriptString(eventName5);
				PlayAudio(eventName5);
				break;

			case 5:
				memset(eventName6, 0, sizeof(eventName6));
				GetTextScriptString(eventName6);
				PlayAudio(eventName6);
				break;

			case 6:
				memset(eventName7, 0, sizeof(eventName7));
				GetTextScriptString(eventName7);
				PlayAudio(eventName7);
				break;

			case 7:
				memset(eventName8, 0, sizeof(eventName8));
				GetTextScriptString(eventName8);
				PlayAudio(eventName8);
				break;
		}

	}
	else if (strncmp(where + 1, "CEV", 3) == 0) // Change EVent (i cant get this to work with the original <PEV event)
	{
		eventNameChoice = GetTextScriptNo(gTS->p_read + 4);
		gTS->p_read += 8;
	}
	else if (strncmp(where + 1, "SEV", 3) == 0) // Stop EVent (This is jank as fuck please fix this later)
	{
		x = GetTextScriptNo(gTS->p_read + 4);

		switch (x)
		{
			default:
				memset(eventName, 0, sizeof(eventName));
				strcpy(eventName, gNull1Name);
				PlayAudio("event:/Null/null0000");
				break;

			case 1:
				memset(eventName2, 0, sizeof(eventName2));
				PlayAudio("event:/Null/null0001");
				break;

			case 2:
				memset(eventName3, 0, sizeof(eventName3));
				PlayAudio("event:/Null/null0002");
				break;

			case 3:
				memset(eventName4, 0, sizeof(eventName4));
				PlayAudio("event:/Null/null0003");
				break;

			case 4:
				memset(eventName5, 0, sizeof(eventName5));
				PlayAudio("event:/Null/null0004");
				break;

			case 5:
				memset(eventName6, 0, sizeof(eventName6));
				PlayAudio("event:/Null/null0005");
				break;

			case 6:
				memset(eventName7, 0, sizeof(eventName7));
				PlayAudio("event:/Null/null0006");
				break;

			case 7:
				memset(eventName8, 0, sizeof(eventName8));
				PlayAudio("event:/Null/null0007");
				break;
		}
		
		gTS->p_read += 8;
	}
	else if (strncmp(where + 1, "CVP", 3) == 0) // Change eVent Parameter
	{
		gTS->p_read += 4;
		GetTextScriptString(eventParameter);
	}
	else if (strncmp(where + 1, "EVP", 3) == 0) // EVent Parameter
	{
		x = GetTextScriptNo(gTS->p_read + 4);
		FmodMusicInstance->setParameterByName(eventParameter, x, false);
		gTS->p_read += 8;
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