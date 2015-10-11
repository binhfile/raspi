/*
 * lib_spi.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <lib_spi.h>
#include <lib_mem.h>

extern int frw_spiGetDeviceSize();
extern int frw_spiInitDevice(void* frw_dev);


void* lib_spiAllocDevice(){
	int size = sizeof(SPI_DEVICE_INTERNAL) + frw_spiGetDeviceSize() - 1;
	SPI_DEVICE_INTERNAL* dev = (SPI_DEVICE_INTERNAL*)lib_alloc(size);
	if(dev){
		frw_spiInitDevice(dev->frw_device);
	}
	return dev;
}
int   lib_spiFreeDevice(void* dev){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		lib_spiCloseDevice(_dev);
		lib_free(_dev, sizeof(SPI_DEVICE_INTERNAL));
		ret = 0;
	}
	return ret;
}
