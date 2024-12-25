// #ifndef UART0_H_
// #define UART0_H_

// #include <stdint.h>
// #include "inc/hw_memmap.h"

// /*******************************************************************************
//  *                             Preprocessor Macros                             *
//  *******************************************************************************/
// #define UART_DATA_5BITS          0x0
// #define UART_DATA_6BITS          0x1
// #define UART_DATA_7BITS          0x2
// #define UART_DATA_8BITS          0x3
// #define UART_LCRH_WLEN_BITS_POS  5
// #define UART_CTL_UARTEN_MASK     0x00000001
// #define UART_CTL_TXE_MASK        0x00000100
// #define UART_CTL_RXE_MASK        0x00000200
// #define UART_FR_TXFE_MASK        0x00000080
// #define UART_FR_RXFE_MASK        0x00000010

// /*******************************************************************************
//  *                            Functions Prototypes                             *
//  *******************************************************************************/

// extern void UART0_Init(void);

// extern void UART0_SendByte(uint8_t data);

// extern uint8_t UART0_ReceiveByte(void);

// extern void UART0_SendString(const uint8_t *pData);

// extern void UART0_SendInteger(int64_t sNumber);

// #endif

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
// #define PART_TM4C123GH6PM

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

#define COMM_PERIPH SYSCTL_PERIPH_UART0
#define COMM_PERIPH_GPIO SYSCTL_PERIPH_GPIOA
#define COMM_BASE UART0_BASE
#define COMM_BASE_GPIO GPIO_PORTA_BASE

#define COMM_INT INT_UART0

#define COMM_PIN_TX GPIO_PIN_1
#define COMM_PIN_RX GPIO_PIN_0
#define COMM_BAUDRATE 9600

void comm_init(void (*UART0_callback)(void));
void comm_send_byte(uint8_t data);
void comm_send_string(char *data);

#endif