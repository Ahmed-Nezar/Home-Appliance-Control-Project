   #include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "HAL/communication.h"
#include "HAL/door.h"
#include "HAL/relay.h"
#include "HAL/lamp.h"
#include "HAL/lm35.h"
#include "HAL/buzzer.h"

char g_ui8UART0Data;
char door = DOOR_CLOSED;
char g_lamp = LAMP_OFF;

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
        comm_send_string("D#");
        // comm_send_byte('D');
        door = DOOR_OPENED;
    } else {
        comm_send_string("C#");
        // comm_send_byte('C');
        door = DOOR_CLOSED;
    }
    SysCtlDelay(1000000);
    GPIOIntClear(DOOR_PORT, DOOR_PIN);
}

void Lamp_InterruptHandle(){
    SysCtlDelay(1000000);
    g_lamp = !LAMP_status();
    GPIOIntClear(LAMP_PORT, LAMP_PIN);

}

void BUZZER_InterruptHandle(void) {
    static char counter = 0;
    if (counter == 2) {
    char temperature[5] = "T_0#";
    temperature[2] = lm35_get_temperature() + '0';
    comm_send_string(temperature);
    if ((temperature[2] - '0') > 25) {
        buzzer_control(BUZZER_ON);
    } else {
        buzzer_control(BUZZER_OFF);
    }
        counter = 0;
        SysCtlDelay(500000);

    }
    else {
        counter++;
    }
}

int main()
{   
    comm_init(UART0_InterruptHandle);
    door_init(Door_InterruptHandle);
    relay_init();
    LAMP_init(Lamp_InterruptHandle);
    relay_control(RELAY_1, RELAY_OFF);
    relay_control(RELAY_2, RELAY_OFF);
    lm35_init();
    buzzer_init(BUZZER_InterruptHandle);


    char lamp_state = 0;
    char lamp_uart = 0;

    char outlet_uart = 0;

    while(1)
    {
        if (g_ui8UART0Data == 0)
        {
            // temperature[2] = lm35_get_temperature() + '0';
            // SysCtlDelay(10000000);

            // comm_send_string(temperature);
            

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
