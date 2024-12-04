#ifndef RELAY_H
#define RELAY_H

#include "../utils/types.h"
#include "../utils/bitwise_operations.h"
#include "../utils/tm4c123gh6pm.h"

#define RELAY_1 0
#define RELAY_2 1

#define RELAY_ON 1
#define RELAY_OFF 0

#define RELAY_1_PORT PORTB
#define RELAY_1_PIN PIN1

#define RELAY_2_PORT PORTB
#define RELAY_2_PIN PIN2

void relay_init(void);
void relay_control(uint8 relay, uint8 state);

#endif