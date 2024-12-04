#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define BUZZER_PERIPH SYSCTL_PERIPH_GPIOF
#define BUZZER_PORT GPIO_PORTF_BASE
#define BUZZER_PIN GPIO_PIN_1

#define BUZZER_ON BUZZER_PIN
#define BUZZER_OFF 0

void buzzer_init(void);
void buzzer_control(uint8_t state);

#endif