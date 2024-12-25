#include "lm35.h"

void lm35_init(void) {
    SysCtlPeripheralEnable(LM35_PERIPH);
    while (!SysCtlPeripheralReady(LM35_PERIPH)) {}
    SysCtlPeripheralEnable(LM35_ADC_PERIPH);
    while (!SysCtlPeripheralReady(LM35_ADC_PERIPH)) {}

    
    GPIOPinTypeADC(LM35_PORT, LM35_PIN);
    ADCSequenceConfigure(LM35_ADC_BASE, LM35_ADC_SEQ, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(LM35_ADC_BASE, LM35_ADC_SEQ, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(LM35_ADC_BASE, LM35_ADC_SEQ);
    ADCIntClear(LM35_ADC_BASE, LM35_ADC_SEQ);
}

uint8_t lm35_get_temperature(void) {
    uint32_t ui32TempValueC;
    uint32_t ui32ADC0Value[4];
    ADCProcessorTrigger(LM35_ADC_BASE, LM35_ADC_SEQ);
    while(!ADCIntStatus(LM35_ADC_BASE, LM35_ADC_SEQ, false)) {}
    ADCIntClear(LM35_ADC_BASE, LM35_ADC_SEQ);
    ADCSequenceDataGet(LM35_ADC_BASE, LM35_ADC_SEQ, ui32ADC0Value);
    ui32TempValueC = (uint8_t)((uint32_t) ((ui32ADC0Value[0] * LM35_MAX_TEMPERATURE * LM35_VREF) / ( LM35_ADC_RESOLUTION * LM35_MAX_VOLTAGE)));
    return ui32TempValueC;
}