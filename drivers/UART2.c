/*
 * UART2.c
 *
 *  Created on: 2019Äê3ÔÂ17ÈÕ
 *      Author: Chan
 */

//UART2
//PD6 RX
//PD7 TX

#include "UART2.h"
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

void UART2IntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32IntStatus);
}

void UART2Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2))
        ;
    HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTD_BASE + GPIO_O_CR) = 0x80;

    //UARTStdioConfig(2,115200,SysCtlClockGet());
    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), 115200,
                                (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                 UART_CONFIG_PAR_NONE));

    GPIOPinTypeUART(GPIO_PORTD_BASE,GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    UARTIntEnable(UART2_BASE,UART_INT_RX);
    IntPrioritySet (INT_UART2, 0xE0);
    //UARTIntRegister(UART2_BASE, UART2IntHandler);
    IntEnable(INT_UART2);
}


