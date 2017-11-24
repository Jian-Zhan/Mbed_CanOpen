#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalIn  button1(BUTTON1);
CAN can1(CAN1_RX, CAN1_TX, 1000000); // rx, tx
char counter = 0;

void send() {
    printf("send()\r\n");
    if(can1.write(CANMessage(1337, &counter, 1))) {
        printf("wloop()\r\n");
        counter++;
        printf("Message sent: %d\r\n", counter);
        led3 = !led3;
    }
}

// main() runs in its own thread in the OS
int main() {
    CANMessage msg;

    while (true) {
        led1 = !led1;
        led2 = button1;
        send();
        wait(0.5);
    }
}

