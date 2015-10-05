/*
 * lib_gpio.h
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#ifndef LIB_INCLUDE_LIB_GPIO_H_
#define LIB_INCLUDE_LIB_GPIO_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "internal/lib_gpio_internal.h"

extern int frw_gpioSetDirectory(void* frw_dev, int dir);
extern int frw_gpioSetInterrupt(void* frw_dev, int intr);
extern int frw_gpioWrite(void* frw_dev, int value);
extern int frw_gpioRead(void* frw_dev);
extern int frw_gpioWaitEvent(void* frw_dev, int timeout);

void* 	lib_gpioAllocDevice(int pinNum);
int   	lib_gpioFreeDevice(void* dev);
#define lib_gpioSetDirectory(dev, dir)		frw_gpioSetDirectory(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, dir)
#define lib_gpioSetInterrupt(dev, intr)		frw_gpioSetInterrupt(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, intr)
#define lib_gpioWrite(dev, value)			frw_gpioWrite(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, value)
#define lib_gpioRead(dev)					frw_gpioRead(((GPIO_DEVICE_INTERNAL*)dev)->frw_device)
#define lib_gpioWaitEvent(dev, timeout)		frw_gpioWaitEvent(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, timeout)
#ifdef __cplusplus
}
#endif
#endif /* LIB_INCLUDE_LIB_GPIO_H_ */
