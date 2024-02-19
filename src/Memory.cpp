#include "Memory.h"

void InitEEPROM()
{
    EEPROM.begin(sizeof(uint32_t) + 1);
    uint8_t FirstTime = 0;
    EEPROM.get(0, FirstTime);
    if (FirstTime != 'T')
    {
        EEPROM.put(0, 'T');
        EEPROM.commit();
        writeTotalMinutesToEEPROM(0);
    }
}

void writeTotalMinutesToEEPROM(uint32_t totalMinutes)
{
    EEPROM.put(1, totalMinutes);
    EEPROM.commit();
}

uint32_t readTotalMinutesFromEEPROM()
{
    uint32_t totalMinutes;
    EEPROM.get(1, totalMinutes);
    Serial.println("Total Minutes: " + String(totalMinutes));
    return totalMinutes;
}