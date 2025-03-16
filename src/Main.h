#pragma once

#include <Windows.h>

#include "cave_story.h"

extern const char* audioDirectory;

extern char gSavePath[MAX_PATH];
extern char gAudioPath[MAX_PATH];

void ReleaseFModBeforeGame();