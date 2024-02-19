#include <Arduino.h>

#include "Memory.h"
#include "GPIO_LED.h"
#include "Communication.h"

void setup()
{
  Serial.begin(115200);
  // connectAWS();
  // InitBuiltinLED();
  InitEEPROM();
}

void loop()
{
  static uint8_t sec = 0;
  uint32_t c = readTotalMinutesFromEEPROM();
  // client.loop();
  delay(1000);
  sec++;
  if (sec >= 60)
  {
    c++;
    writeTotalMinutesToEEPROM(c);
    sec = 0;
  }
}