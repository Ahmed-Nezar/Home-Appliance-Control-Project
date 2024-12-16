#include "lamp.h"

static void (*LAMP_callback)(void) = 0;

void LAMP_InterruptHandle(void) {
    if (LAMP_callback) {
        LAMP_callback();
    }
}

void LAMP_init(void (*LAMP_Interruptfunc)(void)) {
    SysCtlPeripheralEnable(LAMP_PERIPH);
    SysCtlDelay(1);
    GPIOPinTypeGPIOInput(LAMP_PORT, LAMP_PIN);
    GPIOPadConfigSet(LAMP_PORT, LAMP_PIN, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
    // enabe interrupt
    LAMP_callback = LAMP_Interruptfunc;
    GPIOIntTypeSet(LAMP_PORT, LAMP_PIN, GPIO_BOTH_EDGES);
    GPIOIntRegister(LAMP_PORT, LAMP_InterruptHandle);
    GPIOIntEnable(LAMP_PORT, LAMP_PIN);
}

uint8_t LAMP_status(void) {
    return GPIOPinRead(LAMP_PORT, LAMP_PIN);
}


