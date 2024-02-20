#ifndef GPIO_LED_INTERFACE_H
#define GPIO_LED_INTERFACE_H

#include "Common_include.h"

// Micros
#define RED_pin 					        19
#define GREEN_pin 					        21
#define BLUE_pin 					        22
#define WHITE_pin 					        23
    
// For White        
#define Worm_pin 					        19

// Functions defines for portablitiy
#define PIN_MODE(       PIN, MODE  )        pinMode(        PIN, MODE   )
#define ANALOG_WRITE(   PIN, PWM   )        analogWrite(    PIN, PWM    )

#endif