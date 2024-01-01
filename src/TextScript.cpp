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
	char event_name_tsc[MAX_PATH];

	char* where = TextScriptBuffer + gTS->p_read;
	if (where[0] != '<')
		return 0;
	if (strncmp(where + 1, "PEV", 3) == 0) // Play EVent
	{
		gTS->p_read += 4;

		switch (eventNameChoice)
		{
			default:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName, event_name_tsc);
				}
				break;

			case 1:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName2, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName2, event_name_tsc);
				}
				break;

			case 2:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName3, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName3, event_name_tsc);
				}
				break;

			case 3:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName4, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName4, event_name_tsc);
				}
				break;

			case 4:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName5, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName5, event_name_tsc);
				}
				break;

			case 5:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName6, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName6, event_name_tsc);
				}
				break;

			case 6:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName7, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName7, event_name_tsc);
				}
				break;

			case 7:
				memset(event_name_tsc, 0, sizeof(event_name_tsc));
				GetTextScriptString(event_name_tsc);
				if (!(strcmp(eventName8, event_name_tsc) == 0))
				{
					PlayFModAudio(event_name_tsc);
					strcpy(eventName8, event_name_tsc);
				}
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
				PlayFModAudio("event:/Null/null0000");
				break;

			case 1:
				memset(eventName2, 0, sizeof(eventName2));
				PlayFModAudio("event:/Null/null0001");
				break;

			case 2:
				memset(eventName3, 0, sizeof(eventName3));
				PlayFModAudio("event:/Null/null0002");
				break;

			case 3:
				memset(eventName4, 0, sizeof(eventName4));
				PlayFModAudio("event:/Null/null0003");
				break;

			case 4:
				memset(eventName5, 0, sizeof(eventName5));
				PlayFModAudio("event:/Null/null0004");
				break;

			case 5:
				memset(eventName6, 0, sizeof(eventName6));
				PlayFModAudio("event:/Null/null0005");
				break;

			case 6:
				memset(eventName7, 0, sizeof(eventName7));
				PlayFModAudio("event:/Null/null0006");
				break;

			case 7:
				memset(eventName8, 0, sizeof(eventName8));
				PlayFModAudio("event:/Null/null0007");
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