#include "door.h"

void door_init(void) {
    SysCtlPeripheralEnable(DOOR_PERIPH);
    SysCtlDelay(1);
    GPIOPinTypeGPIOInput(DOOR_PORT, DOOR_PIN);
    GPIOPadConfigSet(DOOR_PORT, DOOR_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}

uint8_t door_status(void) {
    return GPIOPinRead(DOOR_PORT, DOOR_PIN);
}