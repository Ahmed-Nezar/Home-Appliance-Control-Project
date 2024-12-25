#include "lamp.h"

static void (*LAMP_callback)(void) = 0; /* This is a function pointer that will be used to call the callback function. */

/* This function is used to handle the lamp interrupt. */
void LAMP_InterruptHandle(void) {
    if (LAMP_callback) {
        LAMP_callback();
    }
}

void LAMP_init(void (*LAMP_Interruptfunc)(void)) {
    SysCtlPeripheralEnable(LAMP_PERIPH);    /* Enable the GPIO port that is used for Lamp. */
    while (!SysCtlPeripheralReady(LAMP_PERIPH)){}   /* Wait for the GPIO port to be ready. */

    GPIOPinTypeGPIOInput(LAMP_PORT, LAMP_PIN);  /* Set the direction of the GPIO port pin as input. */
    GPIOPadConfigSet(LAMP_PORT, LAMP_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);    /* Set the pad configuration of the GPIO port pin. */
    LAMP_callback = LAMP_Interruptfunc;     /* Assign the callback function to the function pointer. */
    GPIOIntTypeSet(LAMP_PORT, LAMP_PIN, GPIO_BOTH_EDGES);   /* Set the interrupt type of the GPIO port pin. */
    GPIOIntRegister(LAMP_PORT, LAMP_InterruptHandle);   /* Register the interrupt handler. */
    GPIOIntEnable(LAMP_PORT, LAMP_PIN);   /* Enable the GPIO port pin interrupt. */
}

uint8_t LAMP_status(void) {
    return GPIOPinRead(LAMP_PORT, LAMP_PIN);
}


