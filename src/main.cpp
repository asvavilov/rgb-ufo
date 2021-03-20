#include <Arduino.h>

// TODO решить с платой с wifi и управлением

// TODO навести порядок (убрать мусор, определиться с библиотекой)

// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include "FastLED.h"
#ifdef __AVR__
#include <avr/power.h>
#endif

#define OUTER_LED_PIN 3
#define INNER_LED_PIN 5

#define OUTER_LED_NUM 24
#define INNER_LED_NUM 6

CRGB innerLeds[INNER_LED_NUM];
CRGB outerLeds[OUTER_LED_NUM];

int outerLedDelay = 10; // delay
unsigned long outerLedTimer = 0;
int innerLedDelay = 500; // delay
unsigned long innerLedTimer = 0;

int rgbCnt = 0;
uint8_t gHue = 0;
uint8_t gHueDelta = 3;

void setup()
{
	FastLED.addLeds<NEOPIXEL, OUTER_LED_PIN>(outerLeds, OUTER_LED_NUM);
	FastLED.addLeds<NEOPIXEL, INNER_LED_PIN>(innerLeds, INNER_LED_NUM);

	randomSeed(analogRead(0));
}

void loop()
{

	// TODO см. управление цветами https://github.com/FastLED/FastLED/wiki/Controlling-leds

	unsigned long ms = millis();

	if (ms > outerLedTimer + outerLedDelay)
	{
		outerLedTimer = ms;

		/*for (int i = 0; i < OUTER_LED_NUM; i++)
		{
			r = (rgbCnt + i) % 3 == 0 ? 255 : 0;
			g = (rgbCnt + i) % 3 == 1 ? 255 : 0;
			b = (rgbCnt + i) % 3 == 2 ? 255 : 0;
			outerLeds[i] = CRGB(r, g, b);
		}*/
		/*// так иногда красный пиксель по всем по кругу пробегает
		gHue += gHueDelta;
		fill_rainbow(outerLeds, OUTER_LED_NUM, gHue, gHueDelta);*/
		gHue += gHueDelta;
		for (int i = 0; i < OUTER_LED_NUM; i++)
		{
			outerLeds[i].setHue((gHue + i * 10) % 255);
		}
	}

	if (ms > innerLedTimer + innerLedDelay)
	{
		innerLedTimer = ms;

		int r = (rgbCnt) % 3 == 2 ? 255 : 0;
		int g = (rgbCnt) % 3 == 1 ? 255 : 0;
		int b = (rgbCnt) % 3 == 0 ? 255 : 0;
		fill_solid(innerLeds, INNER_LED_NUM, CRGB(r, g, b));
		rgbCnt++;
		if (rgbCnt >= 3)
		{
			rgbCnt = 0;
		}
	}

	FastLED.show();
	delay(10);
}
