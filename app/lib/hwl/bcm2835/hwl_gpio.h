/*
 * hwl_gpio.h
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#ifndef LIB_HWL_BCM2835_HWL_GPIO_H_
#define LIB_HWL_BCM2835_HWL_GPIO_H_

#include <hwl_peripheral.h>

#define HWL_GPIO_MEM_BASE		(HWL_PERIPHERAL_MEM_BASE + 0x200000)
#define HWL_GPIO_MEM_LENGTH		(4*1024)

#define HWL_GPIO_MEM_GPPUD		(0x94)
#define HWL_GPIO_MEM_SET		(0x1C)
#define HWL_GPIO_MEM_CLEAR		(0x28)

#define HWL_GPIO_SET_INPUT(mem, pin) 	*(mem+((pin)/10)) &= ~(7<<(((pin)%10)*3))
#define HWL_GPIO_SET_OUTPUT(mem, pin) 	*(mem+((pin)/10)) |=  (1<<(((pin)%10)*3))

#define HWL_GPIO_SET(mem, pin) 			*(mem+HWL_GPIO_MEM_SET+(pin/32)*4) = (1 << (pin%32))
#define HWL_GPIO_CLEAR(mem, pin) 		*(mem+HWL_GPIO_MEM_CLEAR+(pin/32)*4) = (1 << (pin%32))

#define GET_GPIO(g) (*(gpio+13)&(1<<g)) // 0 if LOW, (1<<g) if HIGH

/**
 * @note set pull up/down/none is control ALL gpio pin
 */
#define HWL_GPIO_SET_PULLUP(mem, pin) 	*(mem+HWL_GPIO_MEM_GPPUD) 	= 2
#define HWL_GPIO_SET_PULLDOWN(mem, pin)	*(mem+HWL_GPIO_MEM_GPPUD) 	= 1
#define HWL_GPIO_SET_PULLOFF(mem, pin) 	*(mem+HWL_GPIO_MEM_GPPUD) 	= 0



#endif /* LIB_HWL_BCM2835_HWL_GPIO_H_ */
