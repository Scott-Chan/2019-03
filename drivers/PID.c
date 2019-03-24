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
//    PID_Balance.Err_Last     =  0.0;
//    PID_Balance.Err_2Last    =  0.0;
//    PID_Balance.Integral     =  0.0;
    PID_Balance.Kp           =  7.82;//float //~=8.68  //~=7.82()
    PID_Balance.Ki           =  0.0;//float
    PID_Balance.Kd           =  50.0;//float
    PID_Balance.Output       =  0.0;//float
}

void PID_Position_Init(void)
{
    PID_Position.Target_Value =  0.0;
    PID_Position.Actual_Value =  0.0;
    PID_Position.Err          =  0.0;
//    PID_Position.Err_Last     =  0.0;
//    PID_Position.Err_2Last    =  0.0;
//    PID_Position.Integral     =  0.0;
    PID_Position.Kp           =  0.0;//float
    PID_Position.Ki           =  0.0;//float
    PID_Position.Kd           =  0.0;//float
    PID_Position.Output       =  0.0;//float
}

float PIDBalance_Realize(float Actual)//角度环，Actual = pitch; Target = 0
{
    static float D_Bias,Last_Bias=0;

    PID_Balance.Actual_Value = Actual;
    PID_Balance.Err          = PID_Balance.Target_Value - PID_Balance.Actual_Value;

    D_Bias = PID_Balance.Err - Last_Bias;

    PID_Balance.Output = PID_Balance.Kp*PID_Balance.Err + PID_Balance.Kd*D_Bias;
    Last_Bias = PID_Balance.Err;
    if(PID_Balance.Output<0)
    {
        PID_Balance.Output=-PID_Balance.Output;
    }
    return PID_Balance.Output;
}


