/*
 * lib_gpio.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <lib_gpio.h>
#include <lib_mem.h>
extern int frw_gpioGetDeviceSize();
extern int frw_gpioInit(void* frw_dev, int pinNum);
extern int frw_gpioDestroy(void* frw_dev);

void* 	lib_gpioAllocDevice(int pinNum){
	int size = sizeof(GPIO_DEVICE_INTERNAL) - 1 + frw_gpioGetDeviceSize();
	GPIO_DEVICE_INTERNAL* dev = (GPIO_DEVICE_INTERNAL*)lib_alloc(size);
	if(dev){
		frw_gpioInit(dev, pinNum);
	}
	return dev;
}
int   	lib_gpioFreeDevice(void* dev){
	GPIO_DEVICE_INTERNAL* _dev = (GPIO_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		frw_gpioDestroy(_dev->frw_device);
		lib_free(_dev, sizeof(GPIO_DEVICE_INTERNAL) - 1 + frw_gpioGetDeviceSize());
		ret = 0;
	}
	return ret;
}



