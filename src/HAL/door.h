#ifndef DOOR_H
#define DOOR_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define DOOR_PERIPH SYSCTL_PERIPH_GPIOF
#define DOOR_PORT GPIO_PORTF_BASE
#define DOOR_PIN GPIO_PIN_4

void door_init(void);
uint8_t door_status(void);

#endif