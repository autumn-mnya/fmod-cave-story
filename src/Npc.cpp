#include <Windows.h>
#include <shlwapi.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "Game.h"

#include "main.h"

#include "mod_loader.h"
#include "mod_loader_hooks.h"
#include "cave_story.h"
#include "fmodAudio.h"
#include "TextScript.h"

bool playerIsInFan = false;

// The fan npcs are only replaced if "Replace Fan NPC code" is set to true in settings.ini.

// Fan (left)
void Replacement_ActNpc096(NPCHAR* npc)
{
	RECT rc[3] = {
		{272, 120, 288, 136},
		{288, 120, 304, 136},
		{304, 120, 320, 136},
	};

	switch (npc->act_no)
	{
	case 0:
		if (npc->direct == 2)
			npc->act_no = 2;
		else
			npc->ani_no = 1;

		// Fallthrough
	case 1:
		npc->ani_no = 0;
		break;

	case 2:
		if (++npc->ani_wait > 0)
		{
			npc->ani_wait = 0;
			++npc->ani_no;
		}

		if (npc->ani_no > 2)
			npc->ani_no = 0;

		if (gMC.x > npc->x - (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((WINDOW_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((WINDOW_HEIGHT / 2) + 120) * 0x200))
		{
			if (Random(0, 5) == 1)
				SetNpChar(199, npc->x, npc->y + (Random(-8, 8) * 0x200), 0, 0, 0, NULL, 0x100);
		}

		if (gMC.y < npc->y + (8 * 0x200) && gMC.y > npc->y - (8 * 0x200) && gMC.x < npc->x && gMC.x > npc->x - (96 * 0x200))
		{
			gMC.xm -= 0x88;
			playerIsInFan = true;
			gMC.cond |= 0x20;
		}
		else
			playerIsInFan = false;

		break;
	}

	npc->rect = rc[npc->ani_no];
}

// Fan (up)
void Replacement_ActNpc097(NPCHAR* npc)
{
	RECT rc[3] = {
		{272, 136, 288, 152},
		{288, 136, 304, 152},
		{304, 136, 320, 152},
	};

	switch (npc->act_no)
	{
	case 0:
		if (npc->direct == 2)
			npc->act_no = 2;
		else
			npc->ani_no = 1;

		// Fallthrough
	case 1:
		npc->ani_no = 0;
		break;

	case 2:
		if (++npc->ani_wait > 0)
		{
			npc->ani_wait = 0;
			++npc->ani_no;
		}

		if (npc->ani_no > 2)
			npc->ani_no = 0;

		if (gMC.x > npc->x - (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((WINDOW_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((WINDOW_HEIGHT / 2) + 120) * 0x200))
		{
			if (Random(0, 5) == 1)
				SetNpChar(199, npc->x + (Random(-8, 8) * 0x200), npc->y, 0, 0, 1, NULL, 0x100);
		}

		if (gMC.x < npc->x + (8 * 0x200) && gMC.x > npc->x - (8 * 0x200) && gMC.y < npc->y && gMC.y > npc->y - (96 * 0x200))
		{
			gMC.ym -= 0x88;
			playerIsInFan = true;
		}
		else
			playerIsInFan = false;

		break;
	}

	npc->rect = rc[npc->ani_no];
}

// Fan (right)
void Replacement_ActNpc098(NPCHAR* npc)
{
	RECT rc[3] = {
		{272, 152, 288, 168},
		{288, 152, 304, 168},
		{304, 152, 320, 168},
	};

	switch (npc->act_no)
	{
	case 0:
		if (npc->direct == 2)
			npc->act_no = 2;
		else
			npc->ani_no = 1;

		// Fallthrough
	case 1:
		npc->ani_no = 0;
		break;

	case 2:
		if (++npc->ani_wait > 0)
		{
			npc->ani_wait = 0;
			++npc->ani_no;
		}

		if (npc->ani_no > 2)
			npc->ani_no = 0;

		if (gMC.x > npc->x - (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((WINDOW_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((WINDOW_HEIGHT / 2) + 120) * 0x200))
		{
			if (Random(0, 5) == 1)
				SetNpChar(199, npc->x, npc->y + (Random(-8, 8) * 0x200), 0, 0, 2, NULL, 0x100);
		}

		if (gMC.y < npc->y + (8 * 0x200) && gMC.y > npc->y - (8 * 0x200) && gMC.x < npc->x + (96 * 0x200) && gMC.x > npc->x)
		{
			gMC.xm += 0x88;
			playerIsInFan = true;
			gMC.cond |= 0x20;
		}
		else
			playerIsInFan = false;

		break;
	}

	npc->rect = rc[npc->ani_no];
}

// Fan (down)
void Replacement_ActNpc099(NPCHAR* npc)
{
	RECT rc[3] = {
		{272, 168, 288, 184},
		{288, 168, 304, 184},
		{304, 168, 320, 184},
	};

	switch (npc->act_no)
	{
	case 0:
		if (npc->direct == 2)
			npc->act_no = 2;
		else
			npc->ani_no = 1;

		// Fallthrough
	case 1:
		npc->ani_no = 0;
		break;

	case 2:
		if (++npc->ani_wait > 0)
		{
			npc->ani_wait = 0;
			++npc->ani_no;
		}

		if (npc->ani_no > 2)
			npc->ani_no = 0;

		if (gMC.x > npc->x - (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.x < npc->x + (((WINDOW_WIDTH / 2) + 160) * 0x200) && gMC.y > npc->y - (((WINDOW_HEIGHT / 2) + 120) * 0x200) && gMC.y < npc->y + (((WINDOW_HEIGHT / 2) + 120) * 0x200))
		{
			if (Random(0, 5) == 1)
				SetNpChar(199, npc->x + (Random(-8, 8) * 0x200), npc->y, 0, 0, 3, NULL, 0x100);
		}

		if (gMC.x < npc->x + (8 * 0x200) && gMC.x > npc->x - (8 * 0x200) && gMC.y < npc->y + (96 * 0x200) && gMC.y > npc->y)
		{
			gMC.ym += 0x88;
			playerIsInFan = true;
		}
		else
			playerIsInFan = false;

		break;
	}

	npc->rect = rc[npc->ani_no];
}