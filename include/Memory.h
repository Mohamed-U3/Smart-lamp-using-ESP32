#ifndef Memory_h
#define Memory_h
// dependancies
#include <Arduino.h>
#include <EEPROM.h>

void InitEEPROM();
void writeTotalMinutesToEEPROM(uint32_t totalMinutes);
uint32_t readTotalMinutesFromEEPROM();

#endif
