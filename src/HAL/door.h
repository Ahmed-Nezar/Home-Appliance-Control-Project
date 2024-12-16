#ifndef DOOR_H
#define DOOR_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define DOOR_PERIPH SYSCTL_PERIPH_GPIOB
#define DOOR_PORT GPIO_PORTB_BASE
#define DOOR_PIN GPIO_PIN_0

enum DOOR_STATUS {
    DOOR_CLOSED = 0,
    DOOR_OPENED = 1
};

void door_init(void (*door_callback)(void));
uint8_t door_status(void);

#endif