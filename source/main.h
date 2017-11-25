
#ifndef MAIN_H
#define MAIN_H

// macros to handle the schedule timer
#define sys_timer			timer_interrupt
#define reset_sys_timer()	timer_interrupt = 0
#define reset_node_id()		change_node_id = 0
// Sample Timebase [us] - used by demo (not the stack)
#define CYCLE_TIME			1000

// interrupt for the main program timing control
void serviceSysTimer();

#endif


