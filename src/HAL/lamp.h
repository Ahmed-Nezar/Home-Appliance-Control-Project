#ifndef LAMP_H
#define LAMP_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define LAMP_PERIPH SYSCTL_PERIPH_GPIOD
#define LAMP_PORT GPIO_PORTD_BASE
#define LAMP_PIN GPIO_PIN_0
#define LAMP_PIN_INT GPIO_INT_PIN_0

typedef enum {
    LAMP_OFF = 0,
    LAMP_ON = 1
} LAMP_STATUS;

void LAMP_init(void (*LAMP_callback)(void));
uint8_t LAMP_status(void);

#endif