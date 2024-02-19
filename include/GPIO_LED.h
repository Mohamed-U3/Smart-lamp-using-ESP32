#ifndef GPIO_LED
#define GPIO_LED

#include <Arduino.h>

// Function Declearation
void InitRGBLamp();
void InitWhiteLamp();
void SetRGBLamp(uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t Intensity);
void SetWhiteLamp(uint8_t Worm, uint8_t Intensity);
void RGBLampTest();
void whiteLampTest();

#endif