#ifndef DOOR_H
#define DOOR_H

#include "../utils/types.h"
#include "../utils/bitwise_operations.h"
#include "../utils/tm4c123gh6pm.h"

#define DOOR_PORT PORTA
#define DOOR_PIN PIN3

void door_init(void);
uint8 door_get_state(void);

#endif