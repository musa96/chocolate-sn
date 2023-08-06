#include <dos.h>
#include "sn.h"
#include "kbd.h"

volatile char keystatus[256], keyfifo[KEYFIFOSIZ], keyfifoplc, keyfifoend;
volatile char readch, oldreadch, extended, keytemp;

void _initkeys(void)
{
	long i;

	keyfifoplc = 0; keyfifoend = 0;
	for(i=0;i<256;i++) keystatus[i] = 0;
    initkeys();  /* rcg06082001 platform driver-specific initialization. */
}


void __interrupt __far keyhandler(void)
{
        /*
         * ryan sez: End Of Interrupt call on DOS. This seems like a
         *  dangerous place to put it, if you ask me, but oh well.  --ryan.
         */
    #ifdef PLATFORM_DOS
    	koutp(0x20,0x20);
    #endif

	oldreadch = readch; readch = _readlastkeyhit();

    #if 0
        printf("keyhandler() got a (0x%X) ... \n", readch);
    #endif

        /*
         * ryan sez: these inp/outp calls read the keyboard state,
         *  reset the keyboard, and put the original state back in.
         *  This is apparently needed on some XTs, but not newer boxes, and
         *  obviously never on Linux.  --ryan.
         */
    #ifdef PLATFORM_DOS
    	keytemp = kinp(0x61); koutp(0x61,keytemp|128); koutp(0x61,keytemp&127);
    #else
        keytemp = readch;
    #endif

	if ((readch|1) == 0xe1) { extended = 128; return; }
	if (oldreadch != readch)
	{
		if ((readch&128) == 0)
		{
			keytemp = readch+extended;
			if (!keystatus[(int) keytemp])
			{
				keystatus[(int) keytemp] = 1;
				keyfifo[(int) keyfifoend] = keytemp;
				keyfifo[(int) (keyfifoend+1)&(KEYFIFOSIZ-1)] = 1;
				keyfifoend = ((keyfifoend+2)&(KEYFIFOSIZ-1));
			}
		}
		else
		{
			keytemp = (readch&127)+extended;
			keystatus[(int) keytemp] = 0;
			keyfifo[(int) keyfifoend] = keytemp;
			keyfifo[(int) (keyfifoend+1)&(KEYFIFOSIZ-1)] = 0;
			keyfifoend = ((keyfifoend+2)&(KEYFIFOSIZ-1));
		}
	}
	extended = 0;
}