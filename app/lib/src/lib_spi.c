/*
 * lib_spi.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <lib_spi.h>
#include <lib_mem.h>
#include "lib_spi_internal.h"

extern int frw_spiGetDeviceSize();
extern int frw_spiInitDevice(void* frw_dev);
extern int frw_spiOpenDevice(void* frm_dev);
extern int frw_spiCloseDevice(void* frm_dev);
extern int frw_spiTransfer(void* frm_dev, const void* tx, void* rx, int length);
extern int frw_spiSetDeviceName(void* frm_dev, const char* deviceName);
extern int frw_spiSetOperationMode(void* frm_dev, int mode);
extern int frw_spiSetLSBFirst(void* frm_dev, int set);
extern int frw_spiSetCSHigh(void* frm_dev, int set);
extern int frw_spiSetDelayDeactiveCS(void* frm_dev, int delay);
extern int frw_spiSetSpeed(void* frm_dev, int speed);
extern int frw_spiSetBitWord(void* frm_dev, int bitPerWord);

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
		lib_free(_dev);
		ret = 0;
	}
	return ret;
}
inline int lib_spiOpenDevice(void* dev){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiOpenDevice(_dev->frw_device);
	}
	return ret;
}
inline int lib_spiCloseDevice(void* dev){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiCloseDevice(_dev->frw_device);
	}
	return ret;
}
inline int lib_spiTransfer(void* dev, const void* tx, void* rx, int length){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiTransfer(_dev->frw_device, tx, rx, length);
	}
	return ret;
}

inline int lib_spiSetDeviceName(void* dev, const char* deviceName){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetDeviceName(_dev->frw_device, deviceName);
	}
	return ret;
}
inline int lib_spiSetOperationMode(void* dev, int mode){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetOperationMode(_dev->frw_device, mode);
	}
	return ret;
}
inline int lib_spiSetLSBFirst(void* dev, int set){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetLSBFirst(_dev->frw_device, set);
	}
	return ret;
}
inline int lib_spiSetCSHigh(void* dev, int set){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetCSHigh(_dev->frw_device, set);
	}
	return ret;
}
inline int lib_spiSetDelayDeactiveCS(void* dev, int delay){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetDelayDeactiveCS(_dev->frw_device, delay);
	}
	return ret;
}
inline int lib_spiSetSpeed(void* dev, int speed){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetSpeed(_dev->frw_device, speed);
	}
	return ret;
}
inline int lib_spiSetBitWord(void* dev, int bitPerWord){
	SPI_DEVICE_INTERNAL* _dev = (SPI_DEVICE_INTERNAL*)dev;
	int ret = -1;
	if(_dev){
		ret = frw_spiSetBitWord(_dev->frw_device, bitPerWord);
	}
	return ret;
}



