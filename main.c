

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
#include "drivers/UART.h"
#include "drivers/UART3.h"
#include "drivers/MODE.h"

extern PID PID_Balance;
extern uint8_t count;
extern volatile bool  bDataReady;
extern uint32_t Ch0Value;
extern uint32_t PWM_DUTY;
int32_t angle;
int32_t angledata[2];
uint8_t i;

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

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
        ;
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1);
    GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1,0);

    LEDInit();
    KEYInit();
    PWMInit();
    UART0Init();
//    UART3Init();
    ADCInit();
//    QEI_Config();
    PID_Balance_Init();
    IntMasterEnable();
    while(1)
    {
        //ADC interrupt
        ADC_Trig();
        while(true != bDataReady)
            ;
        bDataReady = false;
        UARTprintf("ch0:%4umv\n", Ch0Value);
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
//        QEIIntDisable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);
//        if(qei_data_array[0].velocity>0)
//        {
//            QEI_Augledata.Angel_Velocity = (int)(qei_data_array[0].velocity*0.4014+0.5); //x°/s
//        }
//        else
//        {
//            QEI_Augledata.Angel_Velocity = (int)(qei_data_array[0].velocity*0.4014-0.5); //x°/s
//        }
//        QEIIntEnable(QEI0_BASE,QEI_INTDIR | QEI_INTTIMER);

        PWMPulseWidthSet(PWM1_BASE,PWM_OUT_2,
                         (PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*PWM_DUTY) / 100);
        angledata[i] = (((int)Ch0Value-1650)*180/1650.0);
        i++;
        i=i>1?0:i;
        UARTprintf("angle:%3d\n",angledata[i]);
        UARTprintf("duty:%3d\n",PWM_DUTY);
        UARTprintf("Kp:%d\n",(int)(PID_Balance.Kp*100));
        UARTprintf("Kd:%d\n",(int)(PID_Balance.Kd*100));

        //SysCtlDelay(100*(SysCtlClockGet()/3000));
        mode4();
    }
}
