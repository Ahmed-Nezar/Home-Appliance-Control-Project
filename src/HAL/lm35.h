#ifndef LM35_H
#define LM35_H


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/adc.h"

#define LM35_PERIPH SYSCTL_PERIPH_GPIOE
#define LM35_ADC_PERIPH SYSCTL_PERIPH_ADC0
#define LM35_PORT GPIO_PORTE_BASE
#define LM35_PIN GPIO_PIN_3
#define LM35_ADC_BASE ADC0_BASE
#define LM35_ADC_SEQ 3

#define LM35_MAX_VOLTAGE 1.5
#define LM35_MAX_TEMPERATURE 150
#define LM35_VREF 5
#define LM35_ADC_RESOLUTION 4095


void lm35_init(void);
uint8_t lm35_get_temperature(void);

#endif