#include <dos.h>
#include "sn.h"
#include "config.h"
#include "timer.h"

volatile long tick;
long waitclock;

void __interrupt __far timerhandler()
{
	totalclock++;
	tick++;
	updatesounds();
}

void bdelay(int time)
{
	waitclock = time;
	while (waitclock > 0)
	{
		if (tick > 5)
		{
			tick = 0;
			waitclock--;
		}
	}
}

void faketimerhandler(void)
{
}
