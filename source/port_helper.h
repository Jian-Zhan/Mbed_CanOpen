

#ifndef PORT_HELPER_H
#define PORT_HELPER_H

#include "canfestival.h"
#include "mbed.h"

void initHelper();
void serviceHelper();
void serviceCOMCommands();

void printMsg(Message& msg);
void printMsg(CANMessage& msg);

#endif
