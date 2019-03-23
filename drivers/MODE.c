/*
 * MODE.c
 *
 *  Created on: 2019��3��21��
 *      Author: Chan
 */

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

#include "drivers/MODE.h"

extern uint32_t PWM_DUTY;
extern int32_t angledata[2];
static int mode1flag=1;
static int mode2flag=1;

void mode1(void)
{
    PWM_DUTY=72;
    if(mode1flag==1)
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
        SysCtlDelay(50*SysCtlClockGet()/3000);
        mode1flag=0;
    }
    //GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
    if(angledata[0]<0)
    {
        if(angledata[0]-angledata[1]>0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_1);
            SysCtlDelay(300*SysCtlClockGet()/3000);
        }
    }
    else
    {
        if(angledata[0]-angledata[1]<0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
            SysCtlDelay(300*SysCtlClockGet()/3000);
        }
    }
}

void mode2(void)
{
    PWM_DUTY=80;
    if(mode2flag==1)
    {
        GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
        SysCtlDelay(50*SysCtlClockGet()/3000);
        mode2flag=0;
    }
    //GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
    if(angledata[0]<0)
    {
        if(angledata[0]-angledata[1]>0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_1);
            SysCtlDelay(300*SysCtlClockGet()/3000);
        }
    }
    else
    {
        if(angledata[0]-angledata[1]<0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
            SysCtlDelay(300*SysCtlClockGet()/3000);
        }
    }

}

void mode3(void)
{

}

void mode4(void)
{

}

void mode5(void)
{

}

void mode6(void)
{

}