/*
 * own_lib.h
 *
 * Version by Felix Köhnlein
 * 
 *
 */

#ifndef __OWNLIB_H__
#define __OWNLIB_H__

//#define DEBUG 1

#if (DEBUG)
	static char VERSION[] = "XX.YY.ZZ";
	#include <stdio.h>
#endif

#include <stdint.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>

#include <libs/ws2811.h>

#define ARRAY_SIZE(stuff)       (sizeof(stuff) / sizeof(stuff[0]))

// defaults for cmdline options

void sleep_s(double time);

void parseargs(int argc, char **argv, ws2811_t *ws2811);

void matrix_render(void);
void matrix_clear(void);

void lightLED(int ledNum, int red, int green, int blue);
void doAnimation(char scheme[], int red, int green, int blue);

ws2811_return_t initLEDS(int argc, char **argv);
void onExit(void);

#endif /* __OWNLIB_H__ */

