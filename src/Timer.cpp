/**
 * ***********************************************************
 * @file  : Timer.cpp
 * @brief : file contain functionalities of Timers
 * @author: Engineer\ Mohamed Yousry
 * @date  : 20/02/2024
 * ***********************************************************
 */

/*
 * ***********************************************************
 * 						Includes
 * ***********************************************************
 */
#include "Timer.h"

/*
 * ***********************************************************
 * 						Global variables
 * ***********************************************************
 */
Ticker timer;

/*
 * ***********************************************************
 * 						Functions body
 * ***********************************************************
 */

/**
 * ***********************************************************
 * @name  : Timer_event
 * @brief : Function that is called when the timer event fires
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void Timer_event()
{
    if (!TIMER_MIN_COUNT_FLAG)
    {
        TIMER_MIN_COUNT_FLAG = true;
    }
}

/**
 * ***********************************************************
 * @name  : Initialize_Timer
 * @brief : Function that initialize the Timer that will call Timer_event every minutes
 * @author: Engineer\ Mohamed yousry
 * @date  : 20/02/2024
 * @param : void
 * @return: void
 * ***********************************************************
 */
void Initialize_Timer()
{
    TIMER_ATTACH(60, Timer_event);
}