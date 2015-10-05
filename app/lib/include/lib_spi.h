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

void* lib_spiAllocDevice();
int   lib_spiFreeDevice(void* dev);
int lib_spiOpenDevice(void* dev);
int lib_spiCloseDevice(void* dev);
int lib_spiTransfer(void* dev, const void* tx, void* rx, int length);

int lib_spiSetDeviceName(void* dev, const char* deviceName);
int lib_spiSetOperationMode(void* dev, int mode);
int lib_spiSetLSBFirst(void* dev, int set);
int lib_spiSetCSHigh(void* dev, int set);
int lib_spiSetDelayDeactiveCS(void* dev, int delay);
int lib_spiSetSpeed(void* dev, int speed);
int lib_spiSetBitWord(void* dev, int bitPerWord);

#ifdef __cplusplus
}
#endif

#endif /* LIB_INCLUDE_LIB_SPI_H_ */
