/**
 * ***********************************************************
 * @file  : Memory.cpp
 * @brief : file contain functionalities of memory
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * ***********************************************************
 */
/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "Memory.h"

/*
 * ***********************************************************
 * 				local Functions Prototypes
 * ***********************************************************
 */
void        writeTotalMinutesToEEPROM(uint32_t totalMinutes);
uint32_t    readTotalMinutesFromEEPROM();

/*
 * ***********************************************************
 * 						Functions body
 * ***********************************************************
 */

/**
 * ***********************************************************
 * @name  : Memory_Task
 * @brief : Tasks of storing that count of minutes in memory
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
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

/**
 * ***********************************************************
 * @name  : InitEEPROM
 * @brief : Initalize and reserve the Flash memory to store values on it as if it's EEPROM
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
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

/**
 * ***********************************************************
 * @name  : writeTotalMinutesToEEPROM
 * @brief : Write in certain memory position the count in minutes
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void writeTotalMinutesToEEPROM(uint32_t totalMinutes)
{
    EEPROM_PUT(1, totalMinutes);
    EEPROM_COMMIT();
}

/**
 * ***********************************************************
 * @name  : readTotalMinutesFromEEPROM
 * @brief : Read in certain memory position the count in minutes
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: uint32_t -> return total minutes of operating time that was stored in the flash memory
 * ***********************************************************
 */
uint32_t readTotalMinutesFromEEPROM()
{
    uint32_t totalMinutes;
    EEPROM_GET(1, totalMinutes);
    SERIAL_PRINTLN("Total Minutes: " + String(totalMinutes));
    return totalMinutes;
}