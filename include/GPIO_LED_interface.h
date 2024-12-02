/**
 * ***********************************************************
 * @file  : GPIO_LED_interface.h
 * @brief : file contain macros for functions from others
 * 			modules, external global variables/objects.
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
#define RED_pin 					        6
#define GREEN_pin 					        5
#define BLUE_pin 					        19
#define WHITE_pin 					        4
    
// For White        
#define Worm_pin 					        6

// select which pin will trigger the configuration portal when set to LOW
#define TRIGGER_PIN                         3

#define GPIO_CAHANGED_LAMP_PAR_FLAG         Changed_Lamp_par_Flag
#define GPIO_PRESSED_BUTTON_FLAG            global_Pressed_Button_Flag

#define GPIO_LAMP_TYPE_VAR                  global_LAMPTYPE
#define GPIO_INTENSITY_GLOBAL_VAR           global_INTENSITY
#define GPIO_WARMNESS_GLOBAL_VAR            global_WARMNESS
#define GPIO_RED_GLOBAL_VAR                 global_RED_color
#define GPIO_GREEN_GLOBAL_VAR               global_GREEN_color
#define GPIO_BLUE_GLOBAL_VAR                global_BLUE_color

// Functions defines for portablitiy
#define PIN_MODE(       PIN, MODE   )       pinMode(        PIN, MODE   )
#define ANALOG_WRITE(   PIN, PWM    )       analogWrite(    PIN, PWM    )
#define SERIAL_PRINTLN(Micro_string )       Serial.println(Micro_string )
#define DELAY(          Micro_MS    )       delay(          Micro_MS    )

#endif