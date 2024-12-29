#ifndef OLED_UTILS_H
#define OLED_UTILS_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void initializeOLED(Adafruit_SSD1306& display);
void drawArc(int16_t x, int16_t y, int16_t radius, int16_t start_angle, int16_t end_angle, uint16_t color, Adafruit_SSD1306& display);
void drawSignal(int signalLevel, int distance, Adafruit_SSD1306& display);

#endif
