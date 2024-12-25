#include "lm35.h"

void lm35_init(void) {
    SysCtlPeripheralEnable(LM35_PERIPH);    /* Enable the GPIO port that is used for LM35. */
    while (!SysCtlPeripheralReady(LM35_PERIPH)) {}
    SysCtlPeripheralEnable(LM35_ADC_PERIPH);    /* Enable the ADC peripheral that is used for LM35. */
    while (!SysCtlPeripheralReady(LM35_ADC_PERIPH)) {}
    
    GPIOPinTypeADC(LM35_PORT, LM35_PIN);    /* Set the direction of the GPIO port pin as ADC. */
    ADCSequenceConfigure(LM35_ADC_BASE, LM35_ADC_SEQ, ADC_TRIGGER_PROCESSOR, 0);    /* Configure the ADC sequence. */
    ADCSequenceStepConfigure(LM35_ADC_BASE, LM35_ADC_SEQ, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);   /* Configure the ADC sequence step. */
    ADCSequenceEnable(LM35_ADC_BASE, LM35_ADC_SEQ);   /* Enable the ADC sequence. */
}

uint8_t lm35_get_temperature(void) {
    uint32_t TempValueC;    /* This variable is used to store the temperature from ADC. */
    ADCProcessorTrigger(LM35_ADC_BASE, LM35_ADC_SEQ);   /* Trigger the ADC processor. */
    while(!ADCIntStatus(LM35_ADC_BASE, LM35_ADC_SEQ, false)) {}  /* Wait for the ADC interrupt. */
    ADCIntClear(LM35_ADC_BASE, LM35_ADC_SEQ);   /* Clear the ADC interrupt. */
    ADCSequenceDataGet(LM35_ADC_BASE, LM35_ADC_SEQ, &TempValueC);   /* Get the data from the ADC sequence. */
    TempValueC = (uint8_t)((uint32_t) ((TempValueC * LM35_MAX_TEMPERATURE * LM35_VREF) / ( LM35_ADC_RESOLUTION * LM35_MAX_VOLTAGE)));   /* tmp = (ADC_Value * 150 * 5) / (4095 * 1.5) */
    return TempValueC;
}