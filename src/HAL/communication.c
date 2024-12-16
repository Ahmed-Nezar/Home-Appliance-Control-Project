// #include "communication.h"
// #include "../utils/tm4c123gh6pm.h"


// static void GPIO_SetupUART0Pins(void)
// {
//     SYSCTL_RCGCGPIO_R  |= 0x01;         /* Enable clock for GPIO PORTA */
//     while(!(SYSCTL_PRGPIO_R & 0x01));   /* Wait until GPIO PORTA clock is activated and it is ready for access*/
   
//     GPIO_PORTA_AMSEL_R &= 0xFC;         /* Disable Analog on PA0 & PA1 */
//     GPIO_PORTA_DIR_R   &= 0xFE;         /* Configure PA0 as input pin */
//     GPIO_PORTA_DIR_R   |= 0x02;         /* Configure PA1 as output pin */
//     GPIO_PORTA_AFSEL_R |= 0x03;         /* Enable alternative function on PA0 & PA1 */
//     /* Set PMCx bits for PA0 & PA1 with value 1 to use PA0 as UART0 RX pin and PA1 as UART0 Tx pin */
//     GPIO_PORTA_PCTL_R  = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) | 0x00000011;
//     GPIO_PORTA_DEN_R   |= 0x03;         /* Enable Digital I/O on PA0 & PA1 */
// }

// /*******************************************************************************
//  *                         Public Functions Definitions                        *
//  *******************************************************************************/

// void UART0_Init(void) /* UART0 configuration: 1 start, 8 bits data, No Parity, 1 stop bit and 9600BPS */
// {
//     /* Setup UART0 pins PA0 --> U0RX & PA1 --> U0TX */
//     GPIO_SetupUART0Pins();
    
//     SYSCTL_RCGCUART_R |= 0x01;          /* Enable clock for UART0 */
//     while(!(SYSCTL_PRUART_R & 0x01));   /* Wait until UART0 clock is activated and it is ready for access*/
    
//     UART0_CTL_R = 0;                    /* Disable UART0 at the beginning */

//     UART0_CC_R  = 0;                    /* Use System Clock*/
    
//     /* To Configure UART0 with Baud Rate 9600 */
//     UART0_IBRD_R = 104;
//     UART0_FBRD_R = 11;
    
//     /* UART Line Control Rister Settings
//      * BRK = 0 Normal Use
//      * PEN = 0 Disable Parity
//      * EPS = 0 No affect as the parity is disabled
//      * STP2 = 0 1-stop bit at end of the frame
//      * FEN = 0 FIFOs are disabled
//      * WLEN = 0x3 8-bits data frame
//      * SPS = 0 no stick parity
//      */
//     UART0_LCRH_R = (UART_DATA_8BITS << UART_LCRH_WLEN_BITS_POS);
    
//     /* UART Control Rister Settings
//      * RXE = 1 Enable UART Receive
//      * TXE = 1 Enable UART Transmit
//      * HSE = 0 The UART is clocked using the system clock divided by 16
//      * UARTEN = 1 Enable UART
//      */
//     UART0_CTL_R = UART_CTL_UARTEN_MASK | UART_CTL_TXE_MASK | UART_CTL_RXE_MASK;
// }
       
// void UART0_SendByte(uint8_t data)
// {
//     while(!(UART0_FR_R & UART_FR_TXFE_MASK)); /* Wait until the transmit FIFO is empty */
//     UART0_DR_R = data; /* Send the byte */
// }

// uint8_t UART0_ReceiveByte(void)
// {
//     while(UART0_FR_R & UART_FR_RXFE_MASK); /* Wait until the receive FIFO is not empty */
//     return UART0_DR_R; /* Read the byte */
// }

// void UART0_SendString(const uint8_t *pData)
// {
//     uint32_t uCounter =0;
// 	/* Transmit the whole string */
//     while(pData[uCounter] != '\0')
//     {
//         UART0_SendByte(pData[uCounter]); /* Send the byte */
//         uCounter++; /* increment the counter to the next byte */
//     }
// }

// void UART0_SendInteger(int64_t sNumber)
// {

//     uint8_t uDigits[20];
//     int8_t uCounter = 0;

//     /* Send the negative sign in case of negative numbers */
//     if (sNumber < 0)
//     {
//         UART0_SendByte('-');
//         sNumber *= -1;
//     }

//     /* Convert the number to an array of characters */
//     do
//     {
//         uDigits[uCounter++] = sNumber % 10 + '0'; /* Convert each digit to its corresponding ASCI character */
//         sNumber /= 10; /* Remove the already converted digit */
//     }
//     while (sNumber != 0);

//     /* Send the array of characters in a reverse order as the digits were converted from right to left */
//     for( uCounter--; uCounter>= 0; uCounter--)
//     {
//         UART0_SendByte(uDigits[uCounter]);
//     }
// }

#include "communication.h"

static void (*UART0_callback)(void) = 0;

void comm_UART0_InterruptHandle(void)
{
    if (UART0_callback) {
        UART0_callback();
    }
}

void comm_init(void (*UART0_IntHandler)(void)) {
    // Enable UART0 and GPIOA peripherals
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0)) {}

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}

    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 as U0RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 as U0TX
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART0);
    UART0_callback = UART0_IntHandler;
    UARTIntRegister(UART0_BASE, comm_UART0_InterruptHandle);

    UARTEnable(UART0_BASE);
    SysCtlDelay(1000);
}

void comm_send_byte(uint8_t data) {
    while (UARTBusy(UART0_BASE)) {}
    UARTCharPut(UART0_BASE, data);
}

void comm_send_string(char *data) {
    while(*data) {
        comm_send_byte(*data++);
    }
}

// uint8_t comm_receive(void) {
//     while (!UARTCharsAvail(UART0_BASE)) {}
//     return UARTCharGet(UART0_BASE);
// }

// void comm_receive_string(char *data, uint8_t length) {
//     uint8_t i;
//     for(i = 0; i < length; i++) {
//         data[i] = comm_receive();
//     }
//     data[i] = '\0';
// }
