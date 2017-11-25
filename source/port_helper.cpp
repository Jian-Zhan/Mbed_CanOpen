
/* Just for demonstration purposes - consider it a notepad
 *
 * sgrove
 */

#include "port_helper.h"
#include "main.h"

Serial Debug(USBTX, USBRX);
DigitalOut running_status(LED1);

extern uint8_t nodeID;
extern uint8_t change_node_id;
extern uint8_t digital_input[1];

void initHelper()
{
    Debug.baud(115200);
    printf(" CANopen port of CANfestival slave node (DS-401) \n");
}

void serviceHelper()
{
    static uint32_t cnt = 0;
    // indicate that the stack is running
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
            printf("ID: 0x%04X DLC: %d Data(0): 0x%02X\n", msg.id, msg.len, msg.data[0]);
            break;
        case 2:
            printf("ID: 0x%04X DLC: %d Data(0->1): 0x%02X 0x%02X\n", msg.id, msg.len, msg.data[0], msg.data[1]);
            break;
        case 3:
            printf("ID: 0x%04X DLC: %d Data(0->2): 0x%02X 0x%02X 0x%02X\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2]);
            break;
        case 4:
            printf("ID: 0x%04X DLC: %d Data(0->3): 0x%02X 0x%02X 0x%02X 0x%02X\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3]);
            break;
        case 5:
            printf("ID: 0x%04X DLC: %d Data(0->4): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4]);
            break;
        case 6:
            printf("ID: 0x%04X DLC: %d Data(0->5): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5]);
            break;
        case 7:
            printf("ID: 0x%04X DLC: %d Data(0->6): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6]);
            break;
        case 8:
            printf("ID: 0x%04X DLC: %d Data(0->7): 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X\n",
                msg.id, msg.len, msg.data[0], msg.data[1], msg.data[2], msg.data[3], msg.data[4], msg.data[5], msg.data[6], msg.data[7]);
            break;
        default: 
            break;
    }

}

void serviceCOMCommands()
{
    static char msg[64];
    static char w_loc=0;
    if (Debug.readable()){
        // store the data
        if (w_loc < 64){
            msg[w_loc++] = Debug.getc();
        }
        // clear the buffer and try again
        else{
            // clear the buffer
            memset(msg, 0, 64);
            w_loc = 0;
            return;
        }
        // parse the message and act on it
        if ((msg[w_loc-1] == '\r') || (msg[w_loc-1] == '\n') ){
            // process the message and look for something familiar
            if (strncmp(msg, "help", strlen("help")) == 0){
                 // print the help menu
                printf("\t HELP OPTIONS (case sesnitive):\n");
                printf("\t  help - display the available options\n");
                printf("\t  id=xxx - change the node id\n");
                printf("\t  about - get info about the node\n");
                printf("\t  input=x - a decimal number\n");
            }
            else if (strncmp(msg, "id=", strlen("id=")) == 0){
                // change the node ID
                int res = atoi(msg+strlen("id="));
                if ( (res > 0) && (res < 128) ){
                    nodeID = res;
                    printf("the new node_id = %d\n", nodeID);
                    change_node_id = 1;
                }
                else{
                    printf("invalid parameter");
                }
            }
            else if (strncmp(msg, "about", strlen("about")) == 0){
                // our call tag
                printf(" CANopen port of CANfestival slave node (DS-401) \n");
            }
            else if (strncmp(msg, "input=", strlen("input=")) == 0){
                // store the input value
                digital_input[0] = (uint8_t)atoi(msg+strlen("input="));
                printf("you entered %d", digital_input[0]);
            }
            // clear the buffer
            memset(msg, 0, 64);
            w_loc = 0;
        }
    }
}

/*
WDT_IRQHandler           
TIMER0_IRQHandler         
TIMER1_IRQHandler         
TIMER2_IRQHandler         
TIMER3_IRQHandler         
UART0_IRQHandler          
UART1_IRQHandler          
UART2_IRQHandler          
UART3_IRQHandler          
PWM1_IRQHandler           
I2C0_IRQHandler           
I2C1_IRQHandler           
I2C2_IRQHandler           
SPI_IRQHandler            
SSP0_IRQHandler           
SSP1_IRQHandler           
PLL0_IRQHandler           
RTC_IRQHandler            
EINT0_IRQHandler          
EINT1_IRQHandler          
EINT2_IRQHandler          
EINT3_IRQHandler          
ADC_IRQHandler            
BOD_IRQHandler            
USB_IRQHandler            
CAN_IRQHandler            
DMA_IRQHandler          
I2S_IRQHandler            
ENET_IRQHandler       
RIT_IRQHandler          
MCPWM_IRQHandler             
QEI_IRQHandler            
PLL1_IRQHandler           
USBActivity_IRQHandler
CANActivity_IRQHandler
*/
