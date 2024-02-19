#include "Timer.h"

void Timer_event()
{
    uint32_t c = readTotalMinutesFromEEPROM();
    c++;
    writeTotalMinutesToEEPROM(c);
}

void Initialize_Timer()
{
    timer.attach(60, Timer_event);
}