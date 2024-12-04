#include "buzzer.h"

void buzzer_init(void) {
    SysCtlPeripheralEnable(BUZZER_PERIPH);
    SysCtlDelay(1);
    GPIOPinTypeGPIOOutput(BUZZER_PORT, BUZZER_PIN);
}

void buzzer_control(uint8_t state) {
    GPIOPinWrite(BUZZER_PORT, BUZZER_PIN, state);
}