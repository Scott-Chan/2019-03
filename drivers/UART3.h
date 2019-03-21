/*
 * UART3.h
 *
 *  Created on: 2019Äê3ÔÂ17ÈÕ
 *      Author: Chan
 */

#ifndef DRIVERS_UART3_H_
#define DRIVERS_UART3_H_

#include <stdint.h>

extern void UART3Init(void);
extern void UART3IntHandler(void);
extern int UARTDataDeal(uint8_t *pui8Data);


#endif /* DRIVERS_UART3_H_ */
