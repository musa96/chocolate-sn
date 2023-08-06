#include "config.h"
#include "sn.h"
#include "sound.h"
#include "sfx.h"

int pcstics, curnote;
int musicvol;
static char *sn2music[] =
{
	"FUTUR",
	"FLOW",
	"COUN2",
	"RUNNIN",
	"NIGHT",
	"MAJOR",
	"TOWN",
	"HITWL",
	"WORK",
	"MEREMO",
	"IKILL",
	"HORROR",
	"ON_RUN",
	"OPENIN",
	"LITF",
	"THIRD",
	"THEME",
	"COMMEN"
};
int gamemusic[] =
{
	sng_s4,
	sng_s5,
	sng_s11,
	sng_s14,
	sng_s2,
	sng_s6,
	sng_s7,
	sng_s1,
	sng_s14,

	sng_s9,
	sng_s17,
	sng_s24,
	sng_s21,
	sng_s11,
	sng_s15,
	sng_s25,
	sng_s23,
	sng_s12,

	sng_s19,
	sng_s13,
	sng_s16,
	sng_s24,
	sng_s22,
	sng_s7,
	sng_s24,
	sng_s23,
	sng_s28,

	sng_s14,
	sng_s10,
	sng_s20,
	sng_s14,
	sng_s4,
	sng_s13,
	sng_s24,
	sng_s29,
	sng_s14,

	sng_s4,
	sng_s28,
	sng_s14,
	sng_s10,
	sng_s25,
	sng_s21,
	sng_s15,
	sng_s2,
	sng_s14
};

int gamemusic2[] =
{
	sng_Future,
	sng_Flow,
	sng_Count,
	sng_Running,
	sng_Town,
	sng_OnRun,
	sng_Major,
	sng_HitTheWall,
	sng_Work,
	sng_Horror,
	sng_Flow,
	sng_OnRun,
	sng_Town,
	sng_HitTheWall,
	sng_Future,
	sng_Horror,
	sng_Flow,
	sng_Meremo,
	sng_Running,	
	sng_Ikill,
	sng_Count,
	sng_Running,
	sng_Night,
	sng_Major,
	sng_Flow,
	sng_Meremo,
	sng_Running,
	sng_Night,
	sng_Major,
	sng_Opening,
	sng_LITF,
	sng_Third
};
void initsound(void)
{
	SDL_Init(SDL_INIT_AUDIO);
	initsfx();
}

void uninitsound(void)
{
	sfxterm();
}

void playsong(int musicid, int loop)
{
}

void updatesounds(void)
{
}

void setmusicvolume(int vol)
{
}

void fademusic(void)
{
}