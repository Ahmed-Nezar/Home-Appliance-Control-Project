#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"

#define COMM_PERIPH SYSCTL_PERIPH_UART0         /* The peripheral of the UART0 */
#define COMM_PERIPH_GPIO SYSCTL_PERIPH_GPIOA    /* The peripheral of the GPIO port that is used for UART0 */
#define COMM_BASE UART0_BASE                    /* The base of the UART0 */
#define COMM_BASE_GPIO GPIO_PORTA_BASE          /* The base of the GPIO port that is used for UART0 */

#define COMM_INT INT_UART0                      /* The interrupt of the UART0 */

#define COMM_PIN_TX GPIO_PIN_1                  /* The pin of the GPIO port that is used for UART0 TX */
#define COMM_PIN_RX GPIO_PIN_0                  /* The pin of the GPIO port that is used for UART0 RX */
#define COMM_BAUDRATE 9600                      /* The baudrate of the UART0 */

void comm_init(void (*UART0_callback)(void));
void comm_send_byte(uint8_t data);
void comm_send_string(char *data);

#endif