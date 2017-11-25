#ifndef PORT_HELPER_H
#define PORT_HELPER_H

#include "mbed.h"
#include "canfestival.h"

void initSerial();
void blinkLED();

void printMsg(Message& msg);
void printMsg(CANMessage& msg);

#endif
