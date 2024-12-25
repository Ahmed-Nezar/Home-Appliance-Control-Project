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
    IntPrioritySet(INT_UART0, 0x01);
    UARTEnable(UART0_BASE);
    SysCtlDelay(1000);
}

void comm_send_byte(uint8_t data) {
    while (UARTBusy(UART0_BASE)) {}
    UARTCharPut(UART0_BASE, data);
}

void comm_send_string(char *data) {
    while(*data != '#') {
        comm_send_byte(*data);
        data++;
    }
    comm_send_byte('#');
    comm_send_byte('\n');
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
