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

#include "drivers/MODE.h"

uint8_t mode1flag=1;

void mode1(void)
{
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_0);
    if(mode1flag)
    {
        SysCtlDelay(217*(SysCtlClockGet()/3000));
        mode1flag=0;
    }
    else
    {
        SysCtlDelay(437*(SysCtlClockGet()/3000));
    }
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,GPIO_PIN_1);
    SysCtlDelay(437*(SysCtlClockGet()/3000));

}

void mode2(void)
{

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
