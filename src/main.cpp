#include <Arduino.h>

// TODO решить с платой с wifi и управлением

#include "FastLED.h"

#define LED_PIN 2

#define INNER_LED_NUM 6
#define OUTER_LED_NUM 24
#define LED_NUM INNER_LED_NUM + OUTER_LED_NUM

CRGB leds[LED_NUM];

#define OUTER_LED_DELAY 10 // delay
unsigned long outerLedTimer = 0;
#define INNER_LED_DELAY 500 // delay
unsigned long innerLedTimer = 0;

int rgbCnt = 0;
uint8_t gHue = 0;
uint8_t gHueDelta = 3;

void setup()
{
	FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_NUM);

	// если используется random
	//randomSeed(analogRead(0));
}

void loop()
{

	// TODO см. управление цветами https://github.com/FastLED/FastLED/wiki/Controlling-leds

	unsigned long ms = millis();

	if (ms > innerLedTimer + INNER_LED_DELAY)
	{
		innerLedTimer = ms;

		int r = (rgbCnt) % 3 == 2 ? 255 : 0;
		int g = (rgbCnt) % 3 == 1 ? 255 : 0;
		int b = (rgbCnt) % 3 == 0 ? 255 : 0;
		fill_solid(leds, INNER_LED_NUM, CRGB(r, g, b));
		rgbCnt++;
		if (rgbCnt >= 3)
		{
			rgbCnt = 0;
		}
	}

	if (ms > outerLedTimer + OUTER_LED_DELAY)
	{
		outerLedTimer = ms;

		gHue += gHueDelta;
		for (int i = INNER_LED_NUM; i < INNER_LED_NUM + OUTER_LED_NUM; i++)
		{
			leds[i].setHue((gHue + i * 10) % 255);
		}
	}

	FastLED.show();
	delay(10);
}
