/*
 * UART3.c
 *
 *  Created on: 2019Äê3ÔÂ17ÈÕ
 *      Author: Chan
 */

//UART3
//PC6 RX
//PC7 TX

#include "UART3.h"
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

void UART3IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = UARTIntStatus(UART3_BASE, true);
    UARTIntClear(UART3_BASE, ui32IntStatus);
}

void UART3Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART3))
        ;

//    UARTStdioConfig(3,115200,SysCtlClockGet());
    UARTConfigSetExpClk(UART3_BASE, SysCtlClockGet(), 115200,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_PAR_NONE));

    GPIOPinTypeUART(GPIO_PORTC_BASE,GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PC6_U3RX);
    GPIOPinConfigure(GPIO_PC7_U3TX);
    UARTIntEnable(UART3_BASE,UART_INT_RX);
    IntPrioritySet (INT_UART3, 0xE0);
    //UARTIntRegister(UART2_BASE, UART2IntHandler);
    IntEnable(INT_UART3);
}

