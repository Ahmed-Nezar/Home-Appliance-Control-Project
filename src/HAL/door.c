#include "door.h"

static void (*door_callback)(void) = 0;

void door_InterruptHandle(void) {
    if (door_callback) {
        door_callback();
    }
}

void door_init(void (*door_Interruptfunc)(void)) {
    SysCtlPeripheralEnable(DOOR_PERIPH);
    SysCtlDelay(1);
    GPIOPinTypeGPIOInput(DOOR_PORT, DOOR_PIN);
    GPIOPadConfigSet(DOOR_PORT, DOOR_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    door_callback = door_Interruptfunc;
    GPIOIntTypeSet(DOOR_PORT, DOOR_PIN, GPIO_BOTH_EDGES);
    GPIOIntRegister(DOOR_PORT, door_InterruptHandle);
    GPIOIntEnable(DOOR_PORT, DOOR_PIN);
}

uint8_t door_status(void) {
    return GPIOPinRead(DOOR_PORT, DOOR_PIN);
}


