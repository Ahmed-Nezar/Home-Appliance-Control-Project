#include "door.h"

static void (*door_callback)(void) = 0; /* This is a function pointer that will be used to call the callback function. */

/* This function is used to handle the door interrupt. */
void door_InterruptHandle(void) {
    if (door_callback) {
        door_callback();
    }
}

void door_init(void (*door_Interruptfunc)(void)) {
    SysCtlPeripheralEnable(DOOR_PERIPH);    /* Enable the GPIO port that is used for Door. */
    while (!SysCtlPeripheralReady(DOOR_PERIPH)){};    /* Wait for the GPIO port to be ready. */
    GPIOPinTypeGPIOInput(DOOR_PORT, DOOR_PIN);  /* Set the direction of the GPIO port pin as input. */
    GPIOPadConfigSet(DOOR_PORT, DOOR_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);    /* Set the pad configuration of the GPIO port pin. */
    door_callback = door_Interruptfunc;   /* Assign the callback function to the function pointer. */
    GPIOIntTypeSet(DOOR_PORT, DOOR_PIN, GPIO_BOTH_EDGES);   /* Set the interrupt type of the GPIO port pin. */
    GPIOIntRegister(DOOR_PORT, door_InterruptHandle);   /* Register the interrupt handler. */
    GPIOIntEnable(DOOR_PORT, DOOR_PIN);     /* Enable the GPIO port pin interrupt. */
}

uint8_t door_status(void) {
    return GPIOPinRead(DOOR_PORT, DOOR_PIN);    /* Read the status of the GPIO port pin. */
}


