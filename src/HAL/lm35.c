#include "lm35.h"

void lm35_init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlDelay(1);
    GPIOPinTypeADC(LM35_PORT, LM35_PIN);
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
}

uint8_t lm35_get_temperature(void) {
    uint32_t ui32TempValueC;
    uint32_t ui32ADC0Value[4];
    ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false)) {}
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, ui32ADC0Value);
    ui32TempValueC = 3.3 * 100 * (ui32ADC0Value[0] / 4096.0);
    return ui32TempValueC;
}