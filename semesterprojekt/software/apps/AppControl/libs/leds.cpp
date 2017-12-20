/*
 * leds.cpp
 *
 * Version by Felix Köhnlein
 * 
 * to convert the C-Files to C++ for easy use
 */
 
#include "leds.h"
 
LEDs::LEDs(QObject *parent) :
    QObject(parent)
{
}

void LEDs::init(int argc, char* argv[])
{
    if (DEBUG == 1)
    {
        printf("LEDs.init is started\n");
        fflush(stdout);
    }
    ws2811_return_t ret = initLEDS(argc, argv);
    if (DEBUG == 1)
    {
        printf("LEDs.init was called\n");
        printf("result: %s\n", ws2811_get_return_t_str(ret));
        fflush(stdout);
    }
}

void LEDs::lightGlas(int ledNum, int red, int green, int blue)
{
    if (DEBUG == 1)
    {
        printf("LEDs.lightGlass is started %i \n", ledNum);
        fflush(stdout);
    }
    lightLED(ledNum,red,green,blue);
    if (DEBUG == 1)
    {
        printf("LEDs.lightGlass was called \n");
        fflush(stdout);
    }
}

void LEDs::clear()
{
    if (DEBUG == 1)
    {
        printf("LEDs.clear is started\n");
        fflush(stdout);
    }
    matrix_clear();
    matrix_render();
    if (DEBUG == 1)
    {
        printf("LEDs.clear was called\n");
        fflush(stdout);
    }
}

void LEDs::close()
{
    if (DEBUG == 1)
    {
        printf("LEDs.close ist started\n");
        fflush(stdout);
    }
    onExit();
    if (DEBUG == 1)
    {
        printf("LEDs.close was called\n");
        fflush(stdout);
    }
}
