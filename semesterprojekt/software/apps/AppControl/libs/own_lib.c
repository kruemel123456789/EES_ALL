/*
 * own_lib.c
 *
 * Version by Felix Köhnlein
 * 
 *
 */

#include "own_lib.h"

#define TARGET_FREQ             WS2811_TARGET_FREQ
#define GPIO_PIN                18
#define DMA                     5
#define STRIP_TYPE            	WS2811_STRIP_RGB		// WS2812/SK6812RGB integrated chip+leds

#define WIDTH                   4
#define HEIGHT                  1
#define LED_COUNT               4 //(WIDTH * HEIGHT)

int width = WIDTH;
int height = HEIGHT;
int led_count = LED_COUNT;

ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .count = LED_COUNT,
            .invert = 0,
            .brightness = 255,
            .strip_type = STRIP_TYPE,
        },
        [1] =
        {
            .gpionum = 0,
            .count = 0,
            .invert = 0,
            .brightness = 0,
        },
    },
};

ws2811_led_t *matrix;


void sleep_s(double time)
{
	usleep(time * 1000000);
}

void parseargs(int argc, char **argv, ws2811_t *ws2811)
{
	int index;
	int c;

	static struct option longopts[] =
	{
		{"help", no_argument, 0, 'h'},
		{"dma", required_argument, 0, 'd'},
		{"gpio", required_argument, 0, 'g'},
		{"invert", no_argument, 0, 'i'},
		{"clear", no_argument, 0, 'c'},
		{"strip", required_argument, 0, 's'},
		{"height", required_argument, 0, 'y'},
		{"width", required_argument, 0, 'x'},
		{"version", no_argument, 0, 'v'},
		{0, 0, 0, 0}
	};

	while (1)
	{

		index = 0;
		c = getopt_long(argc, argv, "cd:g:his:vx:y:", longopts, &index);

		if (c == -1)
			break;

		switch (c)
		{
		case 0:
			/* handle flag options (array's 3rd field non-0) */
			break;

		case 'h':
			#if (DEBUG)
				fprintf(stderr, "%s version %s\n", argv[0], VERSION);
				fprintf(stderr, "Usage: %s \n"
					"-h (--help)    - this information\n"
					"-s (--strip)   - strip type - rgb, grb, gbr, rgbw\n"
					"-x (--width)   - matrix width (default 8)\n"
					"-y (--height)  - matrix height (default 8)\n"
					"-d (--dma)     - dma channel to use (default 5)\n"
					"-g (--gpio)    - GPIO to use\n"
					"                 If omitted, default is 18 (PWM0)\n"
					"-i (--invert)  - invert pin output (pulse LOW)\n"
					"-c (--clear)   - clear matrix on exit.\n"
					"-v (--version) - version information\n"
					, argv[0]);
			#endif
			exit(-1);

		case 'D':
			break;

		case 'g':
			if (optarg) {
				int gpio = atoi(optarg);
/*
	PWM0, which can be set to use GPIOs 12, 18, 40, and 52. 
	Only 12 (pin 32) and 18 (pin 12) are available on the B+/2B/3B
	PWM1 which can be set to use GPIOs 13, 19, 41, 45 and 53. 
	Only 13 is available on the B+/2B/PiZero/3B, on pin 33
	PCM_DOUT, which can be set to use GPIOs 21 and 31.
	Only 21 is available on the B+/2B/PiZero/3B, on pin 40.
	SPI0-MOSI is available on GPIOs 10 and 38.
	Only GPIO 10 is available on all models.

	The library checks if the specified gpio is available
	on the specific model (from model B rev 1 till 3B)

*/
				ws2811->channel[0].gpionum = gpio;
			}
			break;

		case 'i':
			ws2811->channel[0].invert=1;
			break;

		case 'c':
			break;

		case 'd':
			if (optarg) {
				int dma = atoi(optarg);
				if (dma < 14) {
					ws2811->dmanum = dma;
				} else {
					#if (DEBUG)
						printf ("invalid dma %d\n", dma);
					#endif
					exit (-1);
				}
			}
			break;

		case 'y':
			if (optarg) {
				height = atoi(optarg);
				if (height > 0) {
					ws2811->channel[0].count = height * width;
				} else {
					#if (DEBUG)
						printf ("invalid height %d\n", height);
					#endif
					exit (-1);
				}
			}
			break;

		case 'x':
			if (optarg) {
				width = atoi(optarg);
				if (width > 0) {
					ws2811->channel[0].count = height * width;
				} else {
					#if (DEBUG)
						printf ("invalid width %d\n", width);
					#endif
					exit (-1);
				}
			}
			break;

		case 's':
			if (optarg) {
				if (!strncasecmp("rgb", optarg, 4)) {
					ws2811->channel[0].strip_type = WS2811_STRIP_RGB;
				}
				else if (!strncasecmp("rbg", optarg, 4)) {
					ws2811->channel[0].strip_type = WS2811_STRIP_RBG;
				}
				else if (!strncasecmp("grb", optarg, 4)) {
					ws2811->channel[0].strip_type = WS2811_STRIP_GRB;
				}
				else if (!strncasecmp("gbr", optarg, 4)) {
					ws2811->channel[0].strip_type = WS2811_STRIP_GBR;
				}
				else if (!strncasecmp("brg", optarg, 4)) {
					ws2811->channel[0].strip_type = WS2811_STRIP_BRG;
				}
				else if (!strncasecmp("bgr", optarg, 4)) {
					ws2811->channel[0].strip_type = WS2811_STRIP_BGR;
				}
				else if (!strncasecmp("rgbw", optarg, 4)) {
					ws2811->channel[0].strip_type = SK6812_STRIP_RGBW;
				}
				else if (!strncasecmp("grbw", optarg, 4)) {
					ws2811->channel[0].strip_type = SK6812_STRIP_GRBW;
				}
				else {
					#if (DEBUG)
						printf ("invalid strip %s\n", optarg);
					#endif
					exit (-1);
				}
			}
			break;

		case 'v':
			#if (DEBUG)
				fprintf(stderr, "%s version %s\n", argv[0], VERSION);
			#endif
			exit(-1);

		case '?':
			/* getopt_long already reported error? */
			exit(-1);

		default:
			exit(-1);
		}
	}
}

void matrix_render(void)
{
    int x, y;

    for (x = 0; x < width; x++)
    {
        for (y = 0; y < height; y++)
        {
            ledstring.channel[0].leds[(y * width) + x] = matrix[y * width + x];
        }
    }
    ws2811_render(&ledstring);
}

void matrix_clear(void)
{
    int x, y;

    for (y = 0; y < (height ); y++)
    {
        for (x = 0; x < width; x++)
        {
            matrix[y * width + x] = 0;
        }
    }
}

void lightLED(int ledNum, int red, int green, int blue)
{
	if (red > 255)		{red	= 255;}
	if (red < 0)		{red	= 0;}
	if (green > 255)	{green 	= 255;}
	if (green < 0)		{green 	= 0;}
	if (blue > 255)		{blue 	= 255;}
	if (blue < 0)		{blue 	= 0;}
	
	int color = ((red<<16) + (green<<8) + (blue<<0));
	ledstring.channel[0].leds[ledNum] = color;
	
	ws2811_render(&ledstring);
}

void doAnimation(char scheme[], int red, int green, int blue)
{
	matrix_clear();
	matrix_render();
	ws2811_render(&ledstring);
	
	if (red > 255)		{red	= 255;}
	if (red < 0)		{red	= 0;}
	if (green > 255)	{green 	= 255;}
	if (green < 0)		{green 	= 0;}
	if (blue > 255)		{blue 	= 255;}
	if (blue < 0)		{blue 	= 0;}
	
	int color = ((red<<16) + (green<<8) + (blue<<0));
	
	int timespend = 0;
	
	if (strcmp(scheme, "Blinklicht")==0)
	{
		while (timespend < 5)
		{
			ledstring.channel[0].leds[0] = color;
			ledstring.channel[0].leds[3] = 0x000000;
			ws2811_render(&ledstring);
			sleep_s(0.1);
			ledstring.channel[0].leds[0] = 0x000000;
			ledstring.channel[0].leds[3] = color;
			ws2811_render(&ledstring);
			sleep_s(0.1);
			timespend = timespend + 1;
		}
	}
	
	if (strcmp(scheme, "Strobe")==0)
		while (timespend < 10)
		{
				ledstring.channel[0].leds[0] = color;
				ledstring.channel[0].leds[1] = color;
				ledstring.channel[0].leds[2] = color;
				ledstring.channel[0].leds[3] = color;
				ws2811_render(&ledstring);
				sleep_s(0.01);
				ledstring.channel[0].leds[0] = 0;
				ledstring.channel[0].leds[1] = 0;
				ledstring.channel[0].leds[2] = 0;
				ledstring.channel[0].leds[3] = 0;
				ws2811_render(&ledstring);
				sleep_s(0.1);
				timespend = timespend + 1;
		}
}

void onExit()
{
	matrix_clear();
	matrix_render();

	ws2811_fini(&ledstring);
}

ws2811_return_t initLEDS(int argc, char **argv)
{
	parseargs(argc, argv, &ledstring);
	matrix = malloc(sizeof(ws2811_led_t) * width * height);
	return ws2811_init(&ledstring);
}
