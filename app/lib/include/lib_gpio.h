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
extern int frw_gpioSetPull(void* frw_dev, int pull);

void* 	lib_gpioAllocDevice(int pinNum);
int   	lib_gpioFreeDevice(void* dev);
/**
 * @param dir 0-output, 1-input
 */
#define lib_gpioSetDirectory(dev, dir)		frw_gpioSetDirectory(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, dir)
/**
 * @param intr 0-none, 1-falling, 2-rising, 3-both
 */
#define lib_gpioSetInterrupt(dev, intr)		frw_gpioSetInterrupt(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, intr)
#define lib_gpioWrite(dev, value)		frw_gpioWrite(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, value)
#define lib_gpioRead(dev)			frw_gpioRead(((GPIO_DEVICE_INTERNAL*)dev)->frw_device)
#define lib_gpioWaitEvent(dev, timeout)		frw_gpioWaitEvent(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, timeout)
/**
 * @param pull 0-none, 1-pullup, 2-pulldown
 */
#define lib_gpioSetPull(dev, pull)              frw_gpioSetPull(((GPIO_DEVICE_INTERNAL*)dev)->frw_device, pull)
#ifdef __cplusplus
}
#endif
#endif /* LIB_INCLUDE_LIB_GPIO_H_ */
