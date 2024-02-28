#include <Arduino.h>

#include "Memory.h"
#include "GPIO_LED.h"
#include "Communication.h"
#include "Timer.h"

void setup()
{
  Serial.begin(115200);
  InitBuiltinLED();
  Init_General_GPIO();

  InitEEPROM();
  Initialize_Timer();
}

void loop()
{
  Communication_Task();
  GPIO_Task();
  LED_Task();
  Memory_Task();
}