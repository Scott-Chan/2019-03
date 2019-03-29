/*
 * MODE.c
 *
 *  Created on: 2019Äê3ÔÂ21ÈÕ
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

#include "utils/uartstdio.h"

#include "drivers/MODE.h"
#include "drivers/PID.h"

extern uint32_t PWM_DUTY;
extern int32_t angledata[2];
static int mode1flag=1;
static int mode2flag=1;
static int mode3flag=1;

void mode1(void)
{
    int angle;
    angle = angledata[0];
    PWM_DUTY=70;
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
    if(angle>120||angle<-120)
    {
        SysCtlDelay(10*SysCtlClockGet()/3000);
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
    if(angledata[0]<30&&angledata[0]>-30)
    {
        PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
        if(angledata[0]>0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_1);
        }
        PWM_DUTY=PIDBalance_Realize(angledata[0])+PIDPosition_Realize(angledata[0]);
        PWM_DUTY=PWM_DUTY>100?100:PWM_DUTY;
        PWM_DUTY=PWM_DUTY<=0?1:PWM_DUTY;
    }
    else
    {
        PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, false);
        PWM_DUTY=0;
    }
}

void mode4(void)
{
    if(angledata[0]<40&&angledata[0]>-40)
    {
        PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
        if(angledata[0]>0)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
        }
        else
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_1);
        }
        PWM_DUTY=PIDBalance_Realize(angledata[0])+PIDPosition_Realize(angledata[0]);
        PWM_DUTY=PWM_DUTY>100?100:PWM_DUTY;
        PWM_DUTY=PWM_DUTY<=0?1:PWM_DUTY;
    }
    else
    {
        PWM_DUTY=80;
        if(mode3flag==1)
        {
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
            SysCtlDelay(50*SysCtlClockGet()/3000);
            mode3flag=0;
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
}

void mode5(void)
{

}

void mode6(void)
{

}
