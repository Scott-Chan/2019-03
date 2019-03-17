/*
 * PID.c
 *
 *  Created on: 2019年3月15日
 *      Author: Chan
 */

#include "PID.h"

PID PID_Balance;
PID PID_Position;

void PID_Balance_Init(void)
{
    PID_Balance.Target_Value =  0.0;
    PID_Balance.Actual_Value =  0.0;
    PID_Balance.Err          =  0.0;
    PID_Balance.Err_Last     =  0.0;
    PID_Balance.Err_2Last    =  0.0;
    PID_Balance.Integral     =  0.0;
    PID_Balance.Kp           =  0.0;//float
    PID_Balance.Ki           =  0.0;//float
    PID_Balance.Kd           =  0.0;//float
    PID_Balance.Output       =  0.0;//float
}

void PID_Position_Init(void)
{
    PID_Position.Target_Value =  0.0;
    PID_Position.Actual_Value =  0.0;
    PID_Position.Err          =  0.0;
    PID_Position.Err_Last     =  0.0;
    PID_Position.Err_2Last    =  0.0;
    PID_Position.Integral     =  0.0;
    PID_Position.Kp           =  0.0;//float
    PID_Position.Ki           =  0.0;//float
    PID_Position.Kd           =  0.0;//float
    PID_Position.Output       =  0.0;//float
}

float PIDBalance_Realize(float Actual, float Target)//角度环，Actual = pitch; Target = 0
{
//    static volatile bool Err_Flag;
//    static volatile bool Err_LastFlagStatus;
    static float D_Bias,Last_Bias;
    PID_Balance.Target_Value = Target;
    PID_Balance.Actual_Value = Actual;
    PID_Balance.Err          = PID_Balance.Target_Value - PID_Balance.Actual_Value;
    D_Bias = PID_Balance.Err - Last_Bias;
//    if(PIDBalance.Err > 0)
//        Err_Flag = 1;
//    else
//        Err_Flag = 0;
//    if(Err_LastFlagStatus != Err_Flag)
//    {
//        PIDBalance.Output = 0;
//        GyroX = 0;
//    }
//    else
//        ;
//    Err_LastFlagStatus = Err_Flag;

    PID_Balance.Output = PID_Balance.Kp*PID_Balance.Err + PID_Balance.Kd*D_Bias;
    Last_Bias = PID_Balance.Err;
//    if(PIDBalance.Output < -99)     //
//        PIDBalance.Output = -99;    //
//    else if(PIDBalance.Output > 99) //对输出进行限幅
//        PIDBalance.Output = 99;     //
//    else                             //
//        ;                            //

    return PID_Balance.Output;
}
