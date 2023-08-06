#ifndef SNWIN_H
#define SNWIN_H

#if USE_SDL
#include "SDL.h"
#endif

#define __far
#define __interrupt

#ifdef FP_OFF
#undef FP_OFF
#endif
#define FP_OFF(x) ((long) (x))

#define printchrasm(x,y,ch) printf("%c", (char) (ch & 0xFF))

#define cdecl

#define access _access
#define R_OK 4

#endif