#include "Timer.h"

Ticker timer;

void Timer_event()
{
    if (!TIMER_MIN_COUNT_FLAG)
    {
        TIMER_MIN_COUNT_FLAG = true;
    }
}

void Initialize_Timer()
{
    TIMER_ATTACH(60, Timer_event);
}