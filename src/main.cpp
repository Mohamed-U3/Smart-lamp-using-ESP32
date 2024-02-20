#include <Arduino.h>

#include "Memory.h"
#include "GPIO_LED.h"
#include "Communication.h"
#include "Timer.h"

void setup()
{
  Serial.begin(115200);
  // connectAWS();
  // InitBuiltinLED();
  InitEEPROM();
  Initialize_Timer();
  InitRGBLamp();
}

void loop()
{
  // client.loop();
  LED_Task();
  Memory_Task();
  delay(1000);
}