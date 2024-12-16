#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "HAL/communication.h"
#include "HAL/door.h"
#include "HAL/relay.h"
#include "HAL/lamp.h"
#include "HAL/lm35.h"


char g_ui8UART0Data;
char door = DOOR_CLOSED;
char g_lamp = LAMP_ON;

void UART0_InterruptHandle(void){
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true);

    while(UARTCharsAvail(UART0_BASE)) {
        g_ui8UART0Data = UARTCharGet(UART0_BASE);
    }
    UARTIntClear(UART0_BASE, ui32Status);
}

void Door_InterruptHandle(void) {
    if (door == DOOR_CLOSED) {
        comm_send_byte('D');
        door = DOOR_OPENED;
    } else {
        comm_send_byte('C');
        door = DOOR_CLOSED;
    }
    SysCtlDelay(1000000);
    GPIOIntClear(DOOR_PORT, DOOR_PIN);
}

void Lamp_InterruptHandle(){
    SysCtlDelay(1000000);
    g_lamp = LAMP_status();
    GPIOIntClear(LAMP_PORT, LAMP_PIN);

}

int main()
{   
    comm_init(UART0_InterruptHandle);
    door_init(Door_InterruptHandle);
    relay_init();
    LAMP_init(Lamp_InterruptHandle);
    relay_control(RELAY_1, RELAY_OFF);
    relay_control(RELAY_2, RELAY_OFF);
    char lamp_state = 0;
    char lamp_uart = 0;

    char outlet_uart = 0;


    while(1)
    {
        if (g_ui8UART0Data == 0)
        {

            lamp_state = g_lamp ^ lamp_uart;
            relay_control(RELAY_1, lamp_state);
            relay_control(RELAY_2, outlet_uart);
        }
        else
        {
            switch (g_ui8UART0Data)
            {
                case 'O':
                    lamp_uart = LAMP_ON;
                    break;
                case 'F':
                    lamp_uart = LAMP_OFF;
                    break;
                case 'a':
                    outlet_uart = RELAY_ON;
                    break;
                case 'c':
                    outlet_uart = RELAY_OFF;
                    break;
                
            }
            g_ui8UART0Data = 0;
        }

    }
  return 0;
}
