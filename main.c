

/**
 * main.c
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
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "driverlib/fpu.h"
#include "driverlib/qei.h"

#include "utils/uartstdio.h"

#include "drivers/ADC.h"
#include "drivers/LED.h"
#include "drivers/KEY.h"
#include "drivers/PID.h"
#include "drivers/PWM.h"
#include "drivers/QEI.h"
//#include "drivers/UART.h"
#include "drivers/UART3.h"

extern uint8_t count;
extern volatile bool  bDataReady;
extern uint32_t Ch0Value;
struct
{
    uint32_t    Angel_Pos;      //角度位置
    int32_t     Angel_Velocity; //角速度
}QEI_Augledata;

void main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
    FPULazyStackingEnable();
    FPUEnable();

    LEDInit();
    KEYInit();
    PWMInit();
    UART3Init();
    ADCInit();
    QEI_Config();
    IntMasterEnable();
    while(1)
    {
        //ADC interrupt
        ADC_Trig();
        while(true != bDataReady)
            ;
        bDataReady = false;
//        UARTprintf("ch0:%4umv", Ch0Value);
        //KEY interrupt test
//        switch(count)
//        {
//        case 0:GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0);break;
//        case 1:GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_1);break;
//        case 2:GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_2);break;
//        case 3:GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_3);break;
//        }
        GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0);
        //QEI
        QEIIntDisable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
        if(qei_data_array[0].velocity>0)
        {
            QEI_Augledata.Angel_Velocity = (int)(qei_data_array[0].velocity*0.4014+0.5); //x°/s
        }
        else
        {
            QEI_Augledata.Angel_Velocity = (int)(qei_data_array[0].velocity*0.4014-0.5); //x°/s
        }
        QEIIntEnable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
    }
}
