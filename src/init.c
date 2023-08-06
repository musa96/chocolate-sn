/*====================================================================
  This is a private property of Michael Muniko. You may not distribute
  copy or even hack it, without the permission from Michael Muniko.

  Email: michaelmuniko@gmail.com
  ===================================================================*/
#include <fcntl.h>
#include <malloc.h>
#include <dos.h>
#include <io.h>
#include <sys\stat.h>
#include <sys\types.h>
#include "dat.h"
#include "sn.h"
#include "config.h"
#include "controls.h"
#include "sound.h"
#include "sfx.h"
#include "init.h"
#include "weapon.h"
#include "player.h"
#include "str.h"
#include "kbd.h"
#include "timer.h"
#include "stbar.h"
#include "graphics.h"

#define PROG_ID "Shaw's Nightmare Fotom Pak System Startup 1.9 ["__DATE__"]"
#define PROG_ID2 "Shaw's Nightmare II 1.2 ["__DATE__"]"

extern char datfilename[MAXINDEXES][255];
extern int numdatfiles;

void printstr(short x, short y, char string[81], char attribute)
{
        char character;
        short i, pos;

        pos = (y*80+x)<<1;
        i = 0;
        while (string[i] != 0)
        {
                character = string[i];
                printchrasm(0xb8000+(long)pos,1L,((long)attribute<<8)+(long)character);
                i++;
                pos+=2;
        }
}

int loadopt(void)
{
	long fil;

	if ((fil = open("SN.OPT",O_BINARY|O_RDONLY,S_IREAD)) == -1) return(0);
	read(fil,&detailmode,1);
	read(fil,&screensize,2);
	read(fil,&brightness,2);
	read(fil,&sfxvol,2);
	read(fil,&musicvol,2);
	read(fil,&mousesensitivity,2);
	close(fil);
	return(1);
}

void saveopt(void)
{
	long fil;

	if ((fil = open("SN.OPT",O_BINARY|O_CREAT|O_TRUNC|O_WRONLY,S_IWRITE)) == -1) return;
	write(fil,&detailmode,1);
	write(fil,&screensize,2);
	write(fil,&brightness,2);
	write(fil,&sfxvol,2);
	write(fil,&musicvol,2);
	write(fil,&mousesensitivity,2);
	close(fil);
}

void init(void)
{
	long i, fil;
	char tempbuf[80];

	switch (gamemode)
	{
		case sequel:
		strcpy(tempbuf, PROG_ID2);
		break;
		default:
		strcpy(tempbuf, PROG_ID);
		break;
	}
	printf("		");
    printstr(40-(strlen(tempbuf)>>1),0,tempbuf,0x7E);
	printf("\n");
	printstr(0,24,"                           Copyright 2007-2017 Mickey Productions                   ",0x7E);
	
	printf("\n");
	if (loadconfig() != 0)
	{
		printf("Error opening configuration. Please run SETUP.\n");
		exit(-1);
	}
	if (!loadopt())
	{
		screensize = 8;
		sfxvol = 240;
		musicvol = 240;
		mousesensitivity = 4;
	}
	printf("Initializing resources archive\n");
	for(i=0;i<numdatfiles;i++)
		loaddat(datfilename[i]);
	printf("Loading strings\n");
	loadstrings();
	printf("Initializing Build 3D engine\n");
	setmmxoverlay(0);
	initengine();
	printf("Initializing keyboard\n");
	_initkeys();
	printf("Initializing timer handler\n");
	inittimer();
	printf("Loading tiles\n");
	if (loadpics(tilefilename) == -1)
		error("Cannot load tile file", 6000);
	tilesizx[MIRROR] = 0;
	tilesizy[MIRROR] = 0;
	loadvoxels();
	printf("Initializing status bar\n");
	initstatusbar();
	printf("Initializing weapon animations\n");
	initweapon();
	initmovers();
	if (inputdevice == 1) initmouse();
	for(i=1;i<100;i++)
	{
		sprintf(tempbuf, "SN%.2d.DEM", i);
		if (access(tempbuf, R_OK) == 0)
			numdemos++;		
	}
	printf("There are %d demo(s) in the loop\n", numdemos);
	printf("Initializing sound engine\n");
	initsound();

	initgraph();

	zoom = 768;
	pskyoff[0] = 0; pskyoff[1] = 0; pskybits = 1;
	parallaxtype = 1;
}

void uninit(void)
{
	clearview(0L);
	uninitengine();
	uninitkeys();
	uninittimer();
	uninitsound();
	saveopt();
	setvmode(0x3);
}
