/*
This file is part of CanFestival, a library implementing CanOpen Stack.

Copyright (C): Edouard TISSERANT and Francis DUPIN
mbed Port: sgrove

See COPYING file for copyrights details.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

// Includes for the Canfestival driver
#include "canfestival.h"
#include "canopen_timer.h"
#include "mbed.h"

Ticker  TimerTicker_CAN;
TIMEVAL TimerAlarm_CAN;
TIMEVAL TimerCounter_CAN;

static TIMEVAL last_time_set = TIMEVAL_MAX;

void canTimerTick(void);

void initTimer(void)
{
    TimerCounter_CAN = 0;
    TimerAlarm_CAN   = 0;
    TimerTicker_CAN.attach_us(&canTimerTick, US_TO_TIMEVAL_FACTOR);
}

void setTimer(TIMEVAL value)
{
    TimerAlarm_CAN += value;
}

TIMEVAL getElapsedTime(void)
{
    unsigned long timer = TimerCounter_CAN;	// Copy the value of the running timer
    return timer > last_time_set ? timer - last_time_set : last_time_set - timer;
}

void canTimerTick(void)
{
    TimerCounter_CAN++;
    if(TimerCounter_CAN == TimerAlarm_CAN) {
        last_time_set = TimerCounter_CAN;
        TimeDispatch();
    }
}
