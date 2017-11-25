/**************************************************************
    CAN OPEN SAMPLE - MBED SLAVE DS401
**************************************************************/
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
/******************************************************************************
Project description:
Test project for a DS 401 slave, running on mbed
Short description:

    reads from the COM port and changes ID, input value, ect.
    57600 8-n-1
    "help" will print a list of available commands
    prints rx'd messages to the console
    CAN running at 125k
 

******************************************************************************/

#include "mbed.h"
#include "main.h"
#include "canfestival.h"
#include "can_mbed.h"
#include "mbed_slave.h"
#include "ds401.h"
#include "port_helper.h"

// Set used for main program timing control
Ticker SysTimer;
// flag used by the main program timing control interrupt
volatile uint8_t timer_interrupt = 0;
volatile uint8_t change_node_id = 0;

// CAN - put and take data from the stack
uint8_t nodeID;
uint8_t digital_input[1] = {0};
uint8_t digital_output[1] = {0};
uint8_t last_digital_output;

// read a can message from the stack
static Message m = Message_Initializer;

int main() 
{
    // initialize the helper code - just for debugging
    initHelper();
    SysTimer.attach_us(&serviceSysTimer, CYCLE_TIME);

    // start of CANfestival stack calls
    canInit(1000);              // Initialize the CANopen bus
    initTimer();                // Start timer for the CANopen stack

    // Init the state
    nodeID = 10;                           // node id can be anything (1-127)
    setNodeId (&mbed_slave_Data, nodeID);
    setState(&mbed_slave_Data, Initialisation);
    
    // just keep loopin'
    while(1){
        // Cycle timer, invoke action on every time slice
        if (sys_timer){ 
            // Reset timer
            reset_sys_timer(); 

            // look for host communication to change things
            serviceCOMCommands();
            
            // service ds401 digital inputs and outputs
            digital_input_handler(&mbed_slave_Data, digital_input, sizeof(digital_input));
            digital_output_handler(&mbed_slave_Data, digital_output, sizeof(digital_output));
            
            if (last_digital_output != digital_output[0]){
                // do something
                printf("new output = %d", digital_output[0]);
            }
            // save the last value = IO can get continuously bashed
            last_digital_output = digital_output[0];     

            // Check if CAN address has been changed
            if(change_node_id == 1){
                reset_node_id();
                setState(&mbed_slave_Data, Stopped);               // Stop the node, to change the node ID
                setNodeId(&mbed_slave_Data, nodeID);               // Now the CAN adress is changed
                setState(&mbed_slave_Data, Initialisation);     // Set to Pre_operational, master must boot it again
            }
        }

        // a message was received - pass it to the CANstack
        if (canReceive(&m)){     
            // interrupts need to be disabled here
            __disable_irq();
            // process it
            canDispatch(&mbed_slave_Data, &m);
            // and re-enabled here
            __enable_irq();
            // print it to the console for debugging
            printMsg(m);
        }
    }
}

// ISR for the Ticker
void serviceSysTimer()
{
    // just used for debugging purposes
    serviceHelper();
    // set a flag cleared by the main loop
    timer_interrupt = 1;
}

