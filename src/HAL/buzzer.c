#include "buzzer.h"

void (*BUZZER_callback)(void) = 0;  /* This is a function pointer that will be used to call the callback function. */

/* This function is used to handle the SysTick interrupt. */
void BUZZER_SysTick_InterruptHandle(void) {
    if (BUZZER_callback) {
        BUZZER_callback();
    }
}

void Systick_Timer_Init(void)
{
    SysTickPeriodSet(SysCtlClockGet()); /* Set the period of the SysTick counter to System Clock so that it will generate an interrupt every 1 second. */
    SysTickIntEnable(); /* Enable the SysTick interrupt. */
    SysTickIntRegister(BUZZER_SysTick_InterruptHandle); /* Register the SysTick interrupt handler. */
    SysTickEnable();    /* Enable the SysTick counter. */
}

void buzzer_init(void (*BUZZER_Interruptfunc)(void)) {
    SysCtlPeripheralEnable(BUZZER_PERIPH);  /* Enable the GPIO port that is used for Buzzer. */
    while (!SysCtlPeripheralReady(BUZZER_PERIPH)){};  /* Wait for the GPIO port to be ready. */
    GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN); /* Set the direction of the GPIO port pin as output. */
    BUZZER_callback = BUZZER_Interruptfunc; /* Assign the callback function to the function pointer. */
    Systick_Timer_Init(); /* Initialize the SysTick timer. */
}

void buzzer_control(uint8_t state) {
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, state); /* Write the state to the GPIO port pin. */
}