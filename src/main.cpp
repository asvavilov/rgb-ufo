#include <Arduino.h>

// TODO решить с платой с wifi и управлением

// TODO навести порядок (убрать мусор, определиться с библиотекой)

// adafruit (default) or fastled
#define FASTLED

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#ifdef FASTLED
#include "FastLED.h"
#else
#include <Adafruit_NeoPixel.h>
#endif
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            3

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      6

#ifdef FASTLED
CRGB leds[NUMPIXELS];
#endif

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
#ifndef FASTLED
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#endif

int delayval = 100; // delay
char* mode = "rgb"; // random|step|rgb
int r = 0;
int g = 0;
int b = 0;
int cstep = 20;
int rgbCnt = 0;

void setup()
{
	// This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
	if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
	// End of trinket special code
#ifdef FASTLED
	FastLED.addLeds<NEOPIXEL, PIN>(leds, NUMPIXELS);
#else
	pixels.begin(); // This initializes the NeoPixel library.
#endif
	randomSeed(analogRead(0));
}

void loop()
{
	for (int i = 0; i < NUMPIXELS; i++)
	{
		if (mode == "random")
		{
			r = random(255);
			g = random(255);
			b = random(255);
		}
		else if (mode == "step")
		{
			r += cstep;
			if (r > 255)
			{
				r = 0;
				g += cstep;
			}
			if (g > 255)
			{
				g = 0;
				b += cstep;
			}
			if (b > 255)
			{
				b = 0;
			}
		}
		else if (mode == "rgb")
		{
			r = (rgbCnt + i) % 3 == 0 ? 255 : 0;
			g = (rgbCnt + i) % 3 == 1 ? 255 : 0;
			b = (rgbCnt + i) % 3 == 2 ? 255 : 0;
		}
#ifdef FASTLED
		leds[i] = CRGB(r, g, b);
#else
		// pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
		pixels.setPixelColor(i, pixels.Color(r, g, b));
#endif
	}
#ifdef FASTLED
	FastLED.show();
#else
	pixels.show(); // This sends the updated pixel color to the hardware.
#endif
	delay(delayval);
	rgbCnt++;
	if (rgbCnt >= 3)
	{
		rgbCnt = 0;
	}
}
