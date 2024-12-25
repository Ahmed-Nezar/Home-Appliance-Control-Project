#include "relay.h"

/* This function is used to initialize the relay. */
void relay_init(void)
{
    SysCtlPeripheralEnable(RELAY_PERIPH);   /* Enable the GPIO port that is used for Relay. */
    while (!SysCtlPeripheralReady(RELAY_PERIPH)){};   /* Wait for the GPIO port to be ready. */
    GPIOPinTypeGPIOOutput(RELAY_PORT, RELAY_1_PIN | RELAY_2_PIN);   /* Set the direction of the GPIO port pins as output. */
}


void relay_control(uint8_t relay, uint8_t state)
{
    switch (relay)
    {
    case RELAY_1:
        if (state == RELAY_ON)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_1_PIN, RELAY_1_PIN);  /* Turn on the Relay. */
        }
        else if (state == RELAY_OFF)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_1_PIN, 0);   /* Turn off the Relay. */
        }
        break;
    case RELAY_2:
        if (state == RELAY_ON)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_2_PIN, RELAY_2_PIN); /* Turn on the Relay. */

        }
        else if (state == RELAY_OFF)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_2_PIN, 0);   /* Turn off the Relay. */
        }
        break;
    default:
        break;
    }
}