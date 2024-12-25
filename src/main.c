#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "HAL/communication.h"
#include "HAL/door.h"
#include "HAL/relay.h"
#include "HAL/lamp.h"
#include "HAL/lm35.h"
#include "HAL/buzzer.h"

/* Global variables
    * g_ui8UART0Data: The data that is received from UART0
    * g_door: The status of the door from the switch
    * g_lamp: The status of the lamp from the switch
    * g_temp_threshold: The temperature threshold
    */
char g_ui8UART0Data;
char g_door = DOOR_CLOSED;
char g_lamp = LAMP_OFF;
char g_temp_threshold = 30;

/* Function prototypes 
    * delayMS: generate a delay in milliseconds.
    * UART0_InterruptHandle: handle the UART0 interrupt.
    * Door_InterruptHandle: handle the door interrupt.
    * Lamp_InterruptHandle: handle the lamp interrupt.
    * BUZZER_InterruptHandle: handle the buzzer interrupt.
    */
void delayMS(uint32_t ms);
void UART0_InterruptHandle(void);
void Door_InterruptHandle(void);
void Lamp_InterruptHandle(void);
void BUZZER_InterruptHandle(void);

int main()
{   
    /* Initialize the peripherals */
    comm_init(UART0_InterruptHandle);
    door_init(Door_InterruptHandle);
    LAMP_init(Lamp_InterruptHandle);
    lm35_init();
    buzzer_init(BUZZER_InterruptHandle);
    relay_init();
    relay_control(RELAY_1, RELAY_OFF);
    relay_control(RELAY_2, RELAY_OFF);


    char lamp_state = 0;
    char lamp_uart = 0;

    char outlet_uart = 0;

    while(1)
    {
        if (g_ui8UART0Data != 0)
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
        else
        {
            lamp_state = g_lamp ^ lamp_uart;
            relay_control(RELAY_1, lamp_state);
            relay_control(RELAY_2, outlet_uart);
        }

    }
  return 0;
}
\
void delayMS(uint32_t ms) {
    SysCtlDelay( (SysCtlClockGet()/(3*1000))*ms );
}

void UART0_InterruptHandle(void){
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true);

    while(UARTCharsAvail(UART0_BASE)) {
        g_ui8UART0Data = UARTCharGet(UART0_BASE);
    }
    UARTIntClear(UART0_BASE, ui32Status);
}

void Door_InterruptHandle(void) {    
    delayMS(50);
    g_door = !door_status();
    if (g_door == DOOR_OPENED) {
        comm_send_string("D#");
    } else {
        comm_send_string("C#");
    }
    GPIOIntClear(DOOR_PORT, DOOR_PIN);
}

void Lamp_InterruptHandle(){
    delayMS(50);
    g_lamp = !LAMP_status();
    GPIOIntClear(LAMP_PORT, LAMP_PIN);
}

void BUZZER_InterruptHandle(void) {

    char temperature[5] = "T_0#";
    temperature[2] = lm35_get_temperature() + '0';
    comm_send_string(temperature);
    if ((temperature[2] - '0') > g_temp_threshold) {
        buzzer_control(BUZZER_ON);
    } else {
        buzzer_control(BUZZER_OFF);
    }
}