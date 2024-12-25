#ifndef RELAY_H
#define RELAY_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define RELAY_PERIPH SYSCTL_PERIPH_GPIOF    /* The peripheral of the GPIO port that is used for Relay */
#define RELAY_PORT GPIO_PORTF_BASE          /* The base of the GPIO port that is used for Relay */
#define RELAY_1_PIN GPIO_PIN_2              /* The pin of the GPIO port that is used for Relay 1 */
#define RELAY_2_PIN GPIO_PIN_3              /* The pin of the GPIO port that is used for Relay 2 */

typedef enum {
    RELAY_OFF = 0,
    RELAY_ON = 1
} RELAY_STATUS;

#define RELAY_1 1
#define RELAY_2 2

void relay_init(void);
void relay_control(uint8_t relay, uint8_t state);

#endif