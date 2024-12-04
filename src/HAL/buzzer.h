#ifndef BUZZER_H
#define BUZZER_H

#include "../utils/types.h"
#include "../utils/bitwise_operations.h"
#include "../utils/tm4c123gh6pm.h"

#define BUZZER_PORT PORTA
#define BUZZER_PIN PIN4

#define BUZZER_ON 1
#define BUZZER_OFF 0

void buzzer_init(void);
void buzzer_control(uint8 state);

#endif