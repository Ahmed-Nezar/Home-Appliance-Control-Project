#ifndef LM35_H
#define LM35_H

#include "../utils/types.h"
#include "../utils/bitwise_operations.h"
#include "../utils/tm4c123gh6pm.h"

#define LM35_PORT PORTA
#define LM35_PIN PIN2

void lm35_init(void);
uint16 lm35_get_temperature(void);

#endif