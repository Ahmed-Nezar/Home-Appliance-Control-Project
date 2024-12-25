#ifndef DOOR_H
#define DOOR_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#define DOOR_PERIPH SYSCTL_PERIPH_GPIOB /* The peripheral of the GPIO port that is used for Door */
#define DOOR_PORT GPIO_PORTB_BASE       /* The base of the GPIO port that is used for Door */
#define DOOR_PIN GPIO_PIN_0             /* The pin of the GPIO port that is used for Door */

typedef enum {
    DOOR_CLOSED = 0,
    DOOR_OPENED = 1
} DOOR_STATUS;

void door_init(void (*door_callback)(void));
uint8_t door_status(void);

#endif