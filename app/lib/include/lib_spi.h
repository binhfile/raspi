/*
 * lib_spi.h
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#ifndef LIB_INCLUDE_LIB_SPI_H_
#define LIB_INCLUDE_LIB_SPI_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "internal/lib_spi_internal.h"

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


void* 	lib_spiAllocDevice();
int   	lib_spiFreeDevice(void* dev);
#define lib_spiOpenDevice(dev) 					frw_spiOpenDevice (((SPI_DEVICE_INTERNAL*)dev)->frw_device)
#define lib_spiCloseDevice(dev)					frw_spiCloseDevice(((SPI_DEVICE_INTERNAL*)dev)->frw_device)
#define lib_spiTransfer(dev, tx, rx, length) 	frw_spiTransfer(((SPI_DEVICE_INTERNAL*)dev)->frw_device, tx, rx, length)

#define lib_spiSetDeviceName(dev, deviceName) 	frw_spiSetDeviceName(((SPI_DEVICE_INTERNAL*)dev)->frw_device, deviceName)
#define lib_spiSetOperationMode(dev, mode) 		frw_spiSetOperationMode(((SPI_DEVICE_INTERNAL*)dev)->frw_device, mode)
#define lib_spiSetLSBFirst(dev, set) 			frw_spiSetLSBFirst(((SPI_DEVICE_INTERNAL*)dev)->frw_device, set)
#define lib_spiSetCSHigh(dev, set) 				frw_spiSetCSHigh(((SPI_DEVICE_INTERNAL*)dev)->frw_device, set)
#define lib_spiSetDelayDeactiveCS(dev, delay) 	frw_spiSetDelayDeactiveCS(((SPI_DEVICE_INTERNAL*)dev)->frw_device, delay)
#define lib_spiSetSpeed(dev, speed)				frw_spiSetSpeed(((SPI_DEVICE_INTERNAL*)dev)->frw_device, speed)
#define lib_spiSetBitWord(dev, bitPerWord) 		frw_spiSetBitWord(((SPI_DEVICE_INTERNAL*)dev)->frw_device, bitPerWord)

#ifdef __cplusplus
}
#endif

#endif /* LIB_INCLUDE_LIB_SPI_H_ */
