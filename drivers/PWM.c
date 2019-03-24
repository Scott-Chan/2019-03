/*
 * PWM.c
 *
 *  Created on: 2019Äê3ÔÂ15ÈÕ
 *      Author: Chan
 */

//Control PWM
//PE4
//M1PWM2 GEN_1
//DIV1

#include "PWM.h"
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

#define PWM_FREQUENCY 10000
extern uint32_t PWM_DUTY=70;

void PWMInit(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
        ;
    //TODO:Change the PWMDIV
    SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    GPIOPinConfigure(GPIO_PE4_M1PWM2);
    GPIOPinTypePWM(GPIO_PORTE_BASE, GPIO_PIN_4);
    PWMGenConfigure(PWM1_BASE,PWM_GEN_1,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
    //TODO:Change the freqency
    PWMGenPeriodSet(PWM1_BASE,PWM_GEN_1,SysCtlClockGet()/PWM_FREQUENCY);
    //TODO:Change the duty
    PWMPulseWidthSet(PWM1_BASE,PWM_OUT_2,
                     (PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*PWM_DUTY) / 100);
    PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM1_BASE, PWM_GEN_1);
}

