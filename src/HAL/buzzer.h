#ifndef BUZZER_H
#define BUZZER_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

#define BUZZER_PERIPH SYSCTL_PERIPH_GPIOF   /* The peripheral of the GPIO port that is used for Buzzer */
#define BUZZER_PORT GPIO_PORTF_BASE         /* The base of the GPIO port that is used for Buzzer */
#define BUZZER_PIN GPIO_PIN_1               /* The pin of the GPIO port that is used for Buzzer */

#define BUZZER_ON BUZZER_PIN                /* The state of the Buzzer when it is on */
#define BUZZER_OFF 0                        /* The state of the Buzzer when it is off */

void buzzer_init(void (*BUZZER_Interruptfunc)(void));
void buzzer_control(uint8_t state);

#endif