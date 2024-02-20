#include <Arduino.h>
#include "GPIO_LED_interface.h"

void InitRGBLamp()
{
  // LED pins configration
  PIN_MODE(RED_pin,   OUTPUT);
  PIN_MODE(GREEN_pin, OUTPUT);
  PIN_MODE(BLUE_pin,  OUTPUT);
  PIN_MODE(WHITE_pin, OUTPUT);
}

void InitWhiteLamp()
{
  // LED pins configration
  PIN_MODE(Worm_pin,  OUTPUT);
  PIN_MODE(WHITE_pin, OUTPUT);
}

void SetRGBLamp(uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t Intensity)
{
  ANALOG_WRITE(RED_pin,     Red       );
  ANALOG_WRITE(GREEN_pin,   Green     );
  ANALOG_WRITE(BLUE_pin,    Blue      );
  ANALOG_WRITE(WHITE_pin,   Intensity );
}

void SetWhiteLamp(uint8_t Worm, uint8_t Intensity)
{
  ANALOG_WRITE(Worm_pin,    Worm      );
  ANALOG_WRITE(WHITE_pin,   Intensity );
}

void LED_Task()
{
  
}

void RGBLampTest()
{
  SetRGBLamp(0, 0, 0, 0); // dark black
  Serial.println("Color Black");
  delay(5000);

  SetRGBLamp(64, 224, 208, 0); // Firoze
  Serial.println("Color Firoze");
  delay(5000);

  SetRGBLamp(222, 49, 99, 0); // Light RED
  Serial.println("Color Light RED");
  delay(5000);

  SetRGBLamp(223, 255, 0, 0); // Yallow Lemmon
  Serial.println("Color Yallow Lemmon");
  delay(5000);

  SetRGBLamp(255, 127, 80, 0); // Orange
  Serial.println("Color Orange");
  delay(5000);

  SetRGBLamp(255, 255, 0, 0); // Yellow
  Serial.println("Color Yellow");
  delay(5000);

  SetRGBLamp(255, 0, 255, 0); // Magenta
  Serial.println("Color Magenta");
  delay(5000);

  SetRGBLamp(0, 255, 255, 0); // Cyan
  Serial.println("Color Cyan");
  delay(5000);
}

void whiteLampTest()
{
  SetWhiteLamp(255, 255);
  Serial.println("Full white and Worm");
  delay(5000);

  SetWhiteLamp(128, 128);
  Serial.println("Half white and Worm");
  delay(5000);

  SetWhiteLamp(255, 128);
  Serial.println("Half white and Full Worm");
  delay(5000);

  SetWhiteLamp(255, 0);
  Serial.println("Zero white and Full Worm");
  delay(5000);

  SetWhiteLamp(128, 255);
  Serial.println("Full white and Half Worm");
  delay(5000);

  SetWhiteLamp(0, 255);
  Serial.println("Full white and Zero Worm");
  delay(5000);

  SetWhiteLamp(0, 0);
  Serial.println("Zero white and Zero Worm");
  delay(5000);
}