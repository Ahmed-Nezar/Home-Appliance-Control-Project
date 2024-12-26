#include "communication.h"

static void (*UART0_callback)(void) = 0;

void comm_UART0_InterruptHandle(void)
{
    if (UART0_callback) {
        UART0_callback();
    }
}

void comm_init(void (*UART0_IntHandler)(void)) {
    /* Enable the UART0 peripheral and wait for it to be ready. */
    SysCtlPeripheralEnable(COMM_PERIPH);
    while (!SysCtlPeripheralReady(COMM_PERIPH)) {}

    /* Enable the GPIO peripheral and wait for it to be ready. */
    SysCtlPeripheralEnable(COMM_PERIPH_GPIO);
    while (!SysCtlPeripheralReady(COMM_PERIPH_GPIO)) {}

    /* Configure the GPIO pins for the UART0 peripheral. */
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(COMM_BASE_GPIO, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART0 peripheral. */
    UARTConfigSetExpClk(COMM_BASE, SysCtlClockGet(), COMM_BAUDRATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    /* Enable the UART0 receive interrupts. */
    UARTIntEnable(COMM_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(COMM_INT);
    UART0_callback = UART0_IntHandler;  /* Assign the callback function to the function pointer. */
    UARTIntRegister(COMM_BASE, comm_UART0_InterruptHandle); /* Register the UART0 interrupt handler. */
    UARTEnable(COMM_BASE);  /* Enable the UART0 peripheral. */
}

void comm_send_byte(uint8_t data) {
    /* Wait for the UART0 to be ready. */
    while (UARTBusy(COMM_BASE)) {}
    UARTCharPut(COMM_BASE, data);
}

void comm_send_string(char *data) {
    /* Send the string until the '#' character. */
    while(*data != '#') {
        comm_send_byte(*data);
        data++;
    }
    comm_send_byte('#');
    comm_send_byte('\n');
}