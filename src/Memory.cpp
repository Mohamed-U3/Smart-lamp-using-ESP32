#include "Memory.h"

void        writeTotalMinutesToEEPROM(uint32_t totalMinutes);
uint32_t    readTotalMinutesFromEEPROM();

void Memory_Task()
{
    if (MEM_MIN_COUNT_FLAG)
    {
        MINUTE_COUNTER = readTotalMinutesFromEEPROM();
        MINUTE_COUNTER++;
        writeTotalMinutesToEEPROM(MINUTE_COUNTER);

        MEM_MIN_COUNT_FLAG = false; // reset the Flag
    }
}

void InitEEPROM()
{
    EEPROM_BEGIN(sizeof(uint32_t) + 1);
    uint8_t FirstTime = 0;
    EEPROM_GET(0, FirstTime);
    if (FirstTime != 'T')
    {
        EEPROM_PUT(0, 'T');
        EEPROM_COMMIT();
        writeTotalMinutesToEEPROM(0);
    }
}

void writeTotalMinutesToEEPROM(uint32_t totalMinutes)
{
    EEPROM_PUT(1, totalMinutes);
    EEPROM_COMMIT();
}

uint32_t readTotalMinutesFromEEPROM()
{
    uint32_t totalMinutes;
    EEPROM_GET(1, totalMinutes);
    SERIAL_PRINTLN("Total Minutes: " + String(totalMinutes));
    return totalMinutes;
}