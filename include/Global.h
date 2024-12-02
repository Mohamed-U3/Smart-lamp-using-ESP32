/**
 * ***********************************************************
 * @file  : Global.h
 * @brief : file contain macros for functions from others
 * 			modules, external global variables.
 * ***********************************************************
 */
#ifndef GLOBAL_H
#define GLOBAL_H

/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include <stdint.h>

/*
 * ***********************************************************
 * 						Global variables
 * ***********************************************************
 */
// Declearation of variabes
extern uint32_t     minutes_counter;
extern bool         minutes_counter_Flag;

extern bool         Changed_Lamp_par_Flag;
extern bool         global_Pressed_Button_Flag;

extern uint8_t      global_RED_color;
extern uint8_t      global_GREEN_color;
extern uint8_t      global_BLUE_color;
extern uint8_t      global_INTENSITY;
extern uint8_t      global_WARMNESS;
extern const char*  global_LAMPTYPE;

#endif