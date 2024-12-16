#include "buzzer.h"

void (*BUZZER_callback)(void) = 0;

void BUZZER_SysTick_InterruptHandle(void) {
    if (BUZZER_callback) {
        BUZZER_callback();
    }
}

void Systick_Timer_Init(void)
{
    SysTickPeriodSet(SysCtlClockGet());
    
    SysTickIntEnable();
    SysTickIntRegister(BUZZER_SysTick_InterruptHandle);
    SysTickEnable();
}

void buzzer_init(void (*BUZZER_Interruptfunc)(void)) {
    SysCtlPeripheralEnable(BUZZER_PERIPH);
    SysCtlDelay(1);
    GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN);
    BUZZER_callback = BUZZER_Interruptfunc;
    Systick_Timer_Init();
}

void buzzer_control(uint8_t state) {
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, state);
}