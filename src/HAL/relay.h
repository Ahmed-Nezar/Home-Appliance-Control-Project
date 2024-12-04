#ifndef RELAY_H
#define RELAY_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define RELAY_PERIPH SYSCTL_PERIPH_GPIOF
#define RELAY_PORT GPIO_PORTF_BASE
#define RELAY_1_PIN GPIO_PIN_1
#define RELAY_2_PIN GPIO_PIN_2
#define RELAY_ON 1
#define RELAY_OFF 0
#define RELAY_1 1
#define RELAY_2 2


void relay_init(void);
void relay_control(uint8_t relay, uint8_t state);

#endif