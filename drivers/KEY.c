/*
 * KEY.c
 *
 *  Created on: 2019Äê3ÔÂ15ÈÕ
 *      Author: Chan
 */

//KEY
//PF0 PF4

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#include "drivers/PID.h"

extern PID PID_Balance;
extern uint8_t count=1;
extern uint32_t PWM_DUTY;

void KEYIntHandler(void)
{
    uint32_t ui32IntStatus;
    ui32IntStatus = GPIOIntStatus(GPIO_PORTF_BASE, true);
    GPIOIntClear(GPIO_PORTF_BASE, ui32IntStatus);
    if((ui32IntStatus & GPIO_PIN_4) == GPIO_PIN_4)
    {
        SysCtlDelay(20*(SysCtlClockGet()/3000));
        if((ui32IntStatus & GPIO_PIN_4) == GPIO_PIN_4)
        {
            //TODO:Key interrupt issue
            //count++;
            //count=count>3?3:count;
            //PWM_DUTY+=1;
            //PWM_DUTY=PWM_DUTY>100?100:PWM_DUTY;
            PID_Balance.Kd+=5;
        }
        GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);
    }
    if((ui32IntStatus & GPIO_PIN_0) == GPIO_PIN_0)
    {
        SysCtlDelay(20*(SysCtlClockGet()/3000));
        if((ui32IntStatus & GPIO_PIN_0) == GPIO_PIN_0)
        {
            //TODO:Key interrupt issue
            //count--;
            //count=count<1?1:count;
            //PWM_DUTY-=1;
            //PWM_DUTY=PWM_DUTY<=0?1:PWM_DUTY;
            PID_Balance.Kd-=5;
        }
        GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_0);
    }
}

void KEYInit(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ;
    //UNLOCK PF0
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x1;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
    GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_FALLING_EDGE);
    //GPIOIntRegister(GPIO_PORTF_BASE, KEYIntHandler);
    IntEnable(INT_GPIOF);
}
