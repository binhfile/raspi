/*
 * frw_spi_internal.h
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#ifndef LIB_FRW_LINUX_FRW_SPI_INTERNAL_H_
#define LIB_FRW_LINUX_FRW_SPI_INTERNAL_H_
#ifdef __cplusplus
extern "C" {
#endif
#define FRW_SPI_DEVICE_NAME_SIZE	512
typedef struct{
	int Loop;
	int CPHA;
	int CPOL;
	int LSBFirst;
	int CSHigh;
	int ThreeWire;
	int NoCS;
	int Ready;

	int CSDelay;
	int Speed;
	int BitWord;
	int DummyBytes;

	int handle;

	char deviceName[FRW_SPI_DEVICE_NAME_SIZE];
}FRW_SPI_DEVICE;


#ifdef __cplusplus
}
#endif
#endif /* LIB_FRW_LINUX_FRW_SPI_INTERNAL_H_ */
