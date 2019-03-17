/*
 * UART.c
 *
 *  Created on: 2019Äê3ÔÂ15ÈÕ
 *      Author: Chan
 */

//UART0
//PA0 RX
//PA1 TX

#include "UART.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"

#include "utils/uartstdio.h"

//TODO:Get and deal data

void UART0IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32IntStatus);
}

void UART0Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0))
        ;
    UARTStdioConfig(0,115200,SysCtlClockGet());
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    UARTIntEnable(UART0_BASE,UART_INT_RX);
    IntPrioritySet (INT_UART0, 0xE0);
    //UARTIntRegister(UART0_BASE, UART0IntHandler);
    IntEnable(INT_UART0);
}

