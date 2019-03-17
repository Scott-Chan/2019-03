/*
 * QEI.h
 *
 *  Created on: 2019Äê3ÔÂ15ÈÕ
 *      Author: Chan
 */

#ifndef DRIVERS_QEI_H_
#define DRIVERS_QEI_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint32_t periph;
    uint32_t base;
    uint32_t swap_flag;
    uint32_t Qinterrupt;

    uint32_t gpio_periph;
    uint32_t gpio_port;
    uint8_t  gpio_pin;
    uint32_t gpio_cfg_a;
    uint32_t gpio_cfg_b;

    int32_t dir;
    int32_t velocity;   /*  unit: pulse edge per second */   //
    int32_t Init_Pos;
    uint32_t Now_Pos;      //0~1040

}user_qei_data_t;

extern user_qei_data_t qei_data_array[2];
//extern void QEI_InitConfig(user_qei_data_t *qei_data);
extern void QEI_Config(void);
extern void QEI0_IRQHandler(void);

#endif /* DRIVERS_QEI_H_ */
