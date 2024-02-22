/**
 * ***********************************************************
 * @file  : GPIO_LED_interface.h
 * @brief : file contain macros for functions from others
 * 			modules
 * ***********************************************************
 */
#ifndef GPIO_LED_INTERFACE_H
#define GPIO_LED_INTERFACE_H

/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "Common_include.h"

/*
 * ***********************************************************
 * 						Defines
 * ***********************************************************
 */
// Micros
#define RED_pin 					        19
#define GREEN_pin 					        21
#define BLUE_pin 					        22
#define WHITE_pin 					        23
    
// For White        
#define Worm_pin 					        19

#define GPIO_LED_WHITE_LAMP_FLAG            White_Lamp_Flag

// Functions defines for portablitiy
#define PIN_MODE(       PIN, MODE   )       pinMode(        PIN, MODE   )
#define ANALOG_WRITE(   PIN, PWM    )       analogWrite(    PIN, PWM    )
#define SERIAL_PRINTLN(Micro_string )       Serial.println(Micro_string )
#define DELAY(          Micro_MS    )       delay(          Micro_MS    )

#endif