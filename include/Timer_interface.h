/**
 * ***********************************************************
 * @file  : Timer_interface.h
 * @brief : file contain macros for functions from others
 * 			modules
 * ***********************************************************
 */
#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

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
// Definition of variabes for portability
#define TIMER_MIN_COUNT_FLAG                            minutes_counter_Flag

/*
 * ***********************************************************
 * 						Prototypes
 * ***********************************************************
 */
// Definition of functions for portability
#define TIMER_ATTACH(Micro_time, Micro_function)        timer.attach(Micro_time, Micro_function)

#endif