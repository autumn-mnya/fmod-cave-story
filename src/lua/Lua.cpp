#include <Windows.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "Lua.h"

#include "../Main.h"
#include "../mod_loader.h"
#include "../cave_story.h"
#include "../ModSettings.h"

#include "../AutPI.h"

#include "../fmodAudio.h"

#define gL GetLuaL()

static int lua_PlayFModEvent(lua_State* L)
{
	const char* eventName = luaL_checkstring(L, 1);
	PlayFModAudio(eventName);
	return 0;
}

static int lua_StopFModEvent(lua_State* L)
{
	StopFmodAllAudio();
	return 0;
}

FUNCTION_TABLE FModFunctionTable[FUNCTION_TABLE_FMOD_SIZE] =
{
	{"PlayEvent", lua_PlayFModEvent},
	{"StopAudio", lua_StopFModEvent}
};

const char* LuaModName = "FMOD";

void SetFMODGlobalString()
{

}

void PushFMODMetadata()
{

}

void SetFMODLua()
{
	PushFunctionTable(gL, "FMOD", FModFunctionTable, FUNCTION_TABLE_FMOD_SIZE, TRUE);
}