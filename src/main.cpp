/**
 * ***********************************************************
 * @file  : main.cpp
 * @brief : file contain the main functions that call all the other tasks and functions
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * ***********************************************************
 */
#include <Arduino.h>

#include "Memory.h"
#include "GPIO_LED.h"
#include "Communication.h"
#include "Timer.h"

/**
 * ***********************************************************
 * @name  : setup
 * @brief : This function has the initalization of Preiphrals from GPIO, EEPROM (using Flash memeory ESP32 has no EEPROM), and Timer.
 * @author: Engineer\ Mohamed Yousry
 * @date  : 28/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void setup()
{
  Serial.begin(115200);
  // InitBuiltinLED();
  Init_General_GPIO();

  InitEEPROM();
  Initialize_Timer();
}

/**
 * ***********************************************************
 * @name  : loop
 * @brief : This function has the Tasks that going to be repeated over and over until the system powered off.
 * @author: Engineer\ Mohamed Yousry
 * @date  : 28/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void loop()
{
  Communication_Task();
  GPIO_Task();
  LED_Task();
  Memory_Task();
}