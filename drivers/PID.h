/*
 * PID.h
 *
 *  Created on: 2019年3月15日
 *      Author: Chan
 */

#ifndef DRIVERS_PID_H_
#define DRIVERS_PID_H_

typedef struct{
    float Target_Value; //目标值
    float Actual_Value; //实际值
    float Err;          //本次偏差值
    float Err_Last;     //上一次偏差值
    float Err_2Last;    //上上一次偏差值
    float Integral;     //对每一次偏差求和得到的积分值
    float Kp, Ki, Kd;   //比例,计分,微分系数
    float Output;       //输出值
}PID;

extern void PID_Balance_Init(void);
extern void PID_Position_Init(void);


#endif /* DRIVERS_PID_H_ */
