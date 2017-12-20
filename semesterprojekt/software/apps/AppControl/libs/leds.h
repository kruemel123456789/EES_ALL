/*
 * leds.h
 *
 * Version by Felix Köhnlein
 *
 */

/*Since this library and the onboard Raspberry Pi audio
both use the PWM, they cannot be used together.  You will need to
blacklist the Broadcom audio kernel module by creating a file
/etc/modprobe.d/snd-blacklist.conf with

    blacklist snd_bcm2835

If the audio device is still loading after blacklisting, you may also
need to comment it out in the /etc/modules file.

On headless systems you may also need to force audio through hdmi
Edit config.txt and add:

    hdmi_force_hotplug=1
    hdmi_force_edid_audio=1

A reboot is required for this change to take effect

Some distributions use audio by default, even if nothing is being played.
If audio is needed, you can use a USB audio device instead.
 */
 
#ifndef LEDS_H
#define LEDS_H

#include <QObject>
#include <QDebug>

#define DEBUG 1


extern "C"
{
    #include "libs/own_lib.h"
}

class LEDs : public QObject
{
    Q_OBJECT

public:
    explicit LEDs(QObject *parent = nullptr);

public slots:
	void init(int argc, char* argv[]);
	void lightGlas(int ledNum, int red, int green, int blue);
	void clear();
	void close();
	
};

#endif // LEDS_H
