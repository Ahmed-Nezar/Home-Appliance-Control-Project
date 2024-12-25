#include "communication.h"

static void (*UART0_callback)(void) = 0;

void comm_UART0_InterruptHandle(void)
{
    if (UART0_callback) {
        UART0_callback();
    }
}

void comm_init(void (*UART0_IntHandler)(void)) {
    SysCtlPeripheralEnable(COMM_PERIPH);
    while (!SysCtlPeripheralReady(COMM_PERIPH)) {}

    SysCtlPeripheralEnable(COMM_PERIPH_GPIO);
    while (!SysCtlPeripheralReady(COMM_PERIPH_GPIO)) {}

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(COMM_BASE_GPIO, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(COMM_BASE, SysCtlClockGet(), COMM_BAUDRATE,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTIntEnable(COMM_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(COMM_INT);
    UART0_callback = UART0_IntHandler;
    UARTIntRegister(COMM_BASE, comm_UART0_InterruptHandle);
    UARTEnable(COMM_BASE);
}

void comm_send_byte(uint8_t data) {
    while (UARTBusy(COMM_BASE)) {}
    UARTCharPut(COMM_BASE, data);
}

void comm_send_string(char *data) {
    while(*data != '#') {
        comm_send_byte(*data);
        data++;
    }
    comm_send_byte('#');
    comm_send_byte('\n');
}