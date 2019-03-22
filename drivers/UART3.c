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

int UARTDataDeal(uint8_t *pui8Data)
{
    if(pui8Data[0]== 0x6D && pui8Data[1]==0x64 && pui8Data[2]==0x31)
    {
        if(pui8Data[3]==0x31)
        {
            return 1;
        }
        else if(pui8Data[3]==0x32)
        {
            return 2;
        }
        else if(pui8Data[3]==0x33)
        {
            return 3;
        }
    }
    return -1;
}


void UART3IntHandler(void)
{
    uint32_t ui32IntStatus;
    uint8_t  ui8RxBuffer[4]={'\0'};
    uint8_t  i = 0;

    ui32IntStatus = UARTIntStatus(UART3_BASE, true);

    UARTIntClear(UART3_BASE, ui32IntStatus);

    while(UARTCharsAvail(UART3_BASE)) {
        ui8RxBuffer[i++] =(uint8_t)UARTCharGetNonBlocking(UART3_BASE);
        if(i > 4) {
            break;
        }
    }

//    if(1 == UARTDataDeal(ui8RxBuffer))
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_1);
//    }
//    else if(2 == UARTDataDeal(ui8RxBuffer))
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_2);
//    }
//    else if(3 == UARTDataDeal(ui8RxBuffer))
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_3);
//    }
//    else
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
//    }
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
    UARTFIFOEnable(UART3_BASE);
    UARTFIFOLevelSet(UART3_BASE,UART_FIFO_TX2_8, UART_FIFO_RX2_8);
    UARTIntEnable(UART3_BASE,UART_INT_RX);
    IntPrioritySet (INT_UART3, 0xE0);
    //UARTIntRegister(UART2_BASE, UART2IntHandler);
    IntEnable(INT_UART3);
}

