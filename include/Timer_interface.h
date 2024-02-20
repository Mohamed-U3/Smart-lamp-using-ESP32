#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#include "Common_include.h"

// Definition of variabes for portability
#define TIMER_MIN_COUNT_FLAG                            minutes_counter_Flag

// Definition of functions for portability
#define TIMER_ATTACH(Micro_time, Micro_function)        timer.attach(Micro_time, Micro_function)

#endif