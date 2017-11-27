/**************************************************************
 *
 * Test project for a CANopen slave, running on mbed
 *
 * 115200 8-n-1
 * CAN running at 1M, default node id: 4
 *
 ***************************************************************/

#include "mbed.h"
#include "canfestival.h"
#include "TestSlave.h"
#include "port_helper.h"
#include "mb.h"
#include "eeprom_flash.h"

#define CAN_NODE_ID 0x04
#define MODBUS_NODE_ID 0x04

// Set used for main program timing control
Ticker SysTimer;

// read a can message from the stack
static Message m = Message_Initializer;

void saveConfig()
{
    UNS16 reg;
    int i;
    volatile int len = 0;

    enableEEPROMWriting();

    for (i = 0; i < len; i++) {
        reg = *(TestSlave_to_be_saved[i].pointer);
        writeEEPROMWord(i, reg);
    }

    disableEEPROMWriting();
}

int main() 
{
    // initialize the helper code - just for debugging
    printf("CANopen Client\n");
    printf("EEPROM %d\n", readEEPROMWord(0));
    SysTimer.attach_us(&blinkLED, 1000);

    // Start of CANopen stack calls
    canInit();              // Initialize the CANopen bus
    initTimer();                // Start timer for the CANopen stack
    setNodeId(&TestSlave_Data, CAN_NODE_ID);
    setState(&TestSlave_Data, Initialisation);

    // Start of Modbus stack calls
    eMBErrorCode eStatus;
    eStatus = eMBInit(MB_RTU, MODBUS_NODE_ID, 0, 115200, MB_PAR_NONE);
    eStatus = eMBEnable();

    // just keep looping
    while(1) {
        // CANopen poll
        if (canReceive(&m)) {
            // interrupts need to be disabled here
            __disable_irq();
            // process it
            canDispatch(&TestSlave_Data, &m);
            // and re-enabled here
            __enable_irq();
            // print it to the console for debugging
            printMsg(m);
            saveConfig();
        }

        // Modbus poll
        (void)eMBPoll();
    }
}

