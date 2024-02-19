#ifndef Timer_h
#define Timer_h

// Dependancies
#include <Arduino.h>
#include <Ticker.h>
#include "Memory.h"

// Declearation
Ticker timer; //  Ticker object for the timer

// Function declearation
void Timer_event();
void Initialize_Timer();

#endif