/*
 * PID.h
 *
 *  Created on: 2019��3��15��
 *      Author: Chan
 */

#ifndef DRIVERS_PID_H_
#define DRIVERS_PID_H_

typedef struct{
    float Target_Value; //Ŀ��ֵ
    float Actual_Value; //ʵ��ֵ
    float Err;          //����ƫ��ֵ
    float Err_Last;     //��һ��ƫ��ֵ
    float Err_2Last;    //����һ��ƫ��ֵ
    float Integral;     //��ÿһ��ƫ����͵õ��Ļ���ֵ
    float Kp, Ki, Kd;   //����,�Ʒ�,΢��ϵ��
    float Output;       //���ֵ
}PID;

extern void PID_Balance_Init(void);
extern void PID_Position_Init(void);


#endif /* DRIVERS_PID_H_ */
