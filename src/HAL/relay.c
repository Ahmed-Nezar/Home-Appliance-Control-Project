#include "relay.h"


void relay_init(void)
{
    SysCtlPeripheralEnable(RELAY_PERIPH);
    SysCtlDelay(1);
    GPIOPinTypeGPIOOutput(RELAY_PORT, RELAY_1_PIN | RELAY_2_PIN);
}


void relay_control(uint8_t relay, uint8_t state)
{
    switch (relay)
    {
    case RELAY_1:
        if (state == RELAY_ON)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_1_PIN, RELAY_1_PIN);
        }
        else if (state == RELAY_OFF)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_1_PIN, 0);
        }
        break;
    case RELAY_2:
        if (state == RELAY_ON)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_2_PIN, RELAY_2_PIN);

        }
        else if (state == RELAY_OFF)
        {
            GPIOPinWrite(RELAY_PORT, RELAY_2_PIN, 0);
        }
        break;
    default:
        break;
    }
}