#include <Arduino.h>
#include "GPIO_LED_interface.h"

void InitRGBLamp()
{
  // LED pins configration
  pinMode(RED_pin, OUTPUT);
  pinMode(GREEN_pin, OUTPUT);
  pinMode(BLUE_pin, OUTPUT);
  pinMode(WHITE_pin, OUTPUT);
}

void InitWhiteLamp()
{
  // LED pins configration
  pinMode(Worm_pin, OUTPUT);
  pinMode(WHITE_pin, OUTPUT);
}

void SetRGBLamp(uint8_t Red, uint8_t Green, uint8_t Blue, uint8_t Intensity)
{
  analogWrite(RED_pin, Red);
  analogWrite(GREEN_pin, Green);
  analogWrite(BLUE_pin, Blue);
  analogWrite(WHITE_pin, Intensity);
}

void SetWhiteLamp(uint8_t Worm, uint8_t Intensity)
{
  analogWrite(Worm_pin, Worm);
  analogWrite(WHITE_pin, Intensity);
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