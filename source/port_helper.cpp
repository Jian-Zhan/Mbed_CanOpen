#include "port_helper.h"

Serial Debug(USBTX, USBRX);
DigitalOut running_status(LED1);

void initSerial()
{
    Debug.baud(115200);
    printf(" CANopen port of CANfestival slave node (DS-401) \r\n");
}

void blinkLED()
{
    static uint32_t cnt = 0;
    // Blink LED1 to indicate that the stack is running
    if (cnt++ > 100){
        cnt = 0;
        running_status = !running_status;
    }
}

void printMsg(Message& msg)
{
    CANMessage m(msg.cob_id, (char*)msg.data, msg.len, static_cast<CANType>(msg.rtr), CANStandard);
    // call the CANMessage formatted method
    printMsg(m);
}

void printMsg(CANMessage& msg)
{
    switch(msg.len){
        case 1:
            printf("ID: 0x%04X DLC: %d Data(0): 0x%02X\r\n", msg.id, msg.len, msg.data[0]);
            break;
        case 2:
            printf("ID: 0x%04X DLC: %d Data(0->1): 0x%02X 0x%02X\r\n", msg.id, msg.len, msg.data[0], msg.data[1]);
            break;
        case 3:
            printf("ID: 0x%04X DLC: %d Data(0->2): 0x%02X 0x%02X 0x%02X\r\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2]);
            break;
        case 4:
            printf("ID: 0x%04X DLC: %d Data(0->3): 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3]);
            break;
        case 5:
            printf("ID: 0x%04X DLC: %d Data(0->4): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4]);
            break;
        case 6:
            printf("ID: 0x%04X DLC: %d Data(0->5): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
            break;
        case 7:
            printf("ID: 0x%04X DLC: %d Data(0->6): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6]);
            break;
        case 8:
            printf("ID: 0x%04X DLC: %d Data(0->7): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\r\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
            break;
        default: 
            break;
    }

}

