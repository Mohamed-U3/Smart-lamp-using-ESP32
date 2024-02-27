#include <Arduino.h>

#include "Memory.h"
#include "GPIO_LED.h"
#include "Communication.h"
#include "Timer.h"

void setup()
{
  Serial.begin(115200);
  // For AWS server Connection
  //localConnect();
  // For AWS server Connection
  //connectAWS();
  InitBuiltinLED();

  InitEEPROM();
  Initialize_Timer();
}

void loop()
{
  Communication_Task();
  LED_Task();
  Memory_Task();
}