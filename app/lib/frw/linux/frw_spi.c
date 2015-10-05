/*
 * frw_spi.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#include "frw_spi_internal.h"
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

inline int frw_spiGetDeviceSize(){
	return sizeof(FRW_SPI_DEVICE);
}
int frw_spiInitDevice(void* frw_dev){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	int i;
	if(dev){
		dev->BitWord = 8;
		dev->CPHA = 0;
		dev->CPOL = 0;
		dev->CSDelay = 0;
		dev->CSHigh = 0;
		dev->DummyBytes = 0;
		dev->LSBFirst = 0;
		dev->Loop = 0;
		dev->NoCS = 0;
		dev->Ready = 0;
		dev->Speed = 100000;
		dev->ThreeWire = 0;
		for(i = 0; i < FRW_SPI_DEVICE_NAME_SIZE; i++){
			dev->deviceName[i] = 0;
		}
		dev->handle = -1;
		ret = 0;
	}
	return ret;
}
unsigned char frw_spiGetCfg(void* frw_dev){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	unsigned char cfg = 0;
	if(dev){
	    if(dev->Loop)     	cfg |= SPI_LOOP;
	    if(dev->CPHA) 		cfg |= SPI_CPHA;
	    if(dev->CPOL) 		cfg |= SPI_CPOL;
	    if(dev->LSBFirst) 	cfg |= SPI_LSB_FIRST;
	    if(dev->CSHigh)   	cfg |= SPI_CS_HIGH;
	    if(dev->ThreeWire)  cfg |= SPI_3WIRE;
	    if(dev->NoCS)     	cfg |= SPI_NO_CS;
	    if(dev->Ready)    	cfg |= SPI_READY;
	}
	return cfg;
}
int frw_spiOpenDevice(void* frw_dev){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	int hdl, err;
	unsigned char cfg;
	if(dev && dev->handle == -1){
		hdl = open(dev->deviceName, O_RDWR);
		if(hdl >= 0){
			cfg = frw_spiGetCfg(dev);
			err = ioctl(hdl, SPI_IOC_WR_MODE, &cfg);
			if(err != -1){
				err = ioctl(hdl, SPI_IOC_WR_BITS_PER_WORD, &dev->BitWord);
			}
			if(err != -1){
				err = ioctl(hdl, SPI_IOC_WR_MAX_SPEED_HZ, &dev->Speed);
			}
			if(err != -1){
				dev->handle = hdl;
				ret = 0;
			}else{
				close(hdl);
			}
		}
	}
	return ret;
}
int frw_spiCloseDevice(void* frw_dev){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev && dev->handle != -1){
		close(dev->handle);
		dev->handle = -1;
		ret = 0;
	}
	return ret;
}
int frw_spiTransfer(void* frw_dev, const void* tx, void* rx, int length){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	struct spi_ioc_transfer tr = {0};
	if(dev && dev->handle != -1){
		tr.tx_buf           = (unsigned long)tx;
		tr.rx_buf           = (unsigned long)rx;
		tr.len              = length;
		tr.delay_usecs      = dev->CSDelay;
		tr.speed_hz         = dev->Speed;
		tr.bits_per_word    = dev->BitWord;
		//tr.cs_change		= true;

		ret = ioctl(dev->handle, SPI_IOC_MESSAGE(1), &tr);
	}
	return ret;
}
int frw_spiSetDeviceName(void* frw_dev, const char* deviceName){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	int i;
	if(dev){
		for(i = 0; i < FRW_SPI_DEVICE_NAME_SIZE; i++){
			if(deviceName[i] == 0) break;
			dev->deviceName[i] = deviceName[i];
		}
		ret = 0;
	}
	return ret;
}
int frw_spiSetOperationMode(void* frw_dev, int mode){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev){
		switch(mode){
		case 0:
			dev->CPHA = 0;
			dev->CPOL = 0;
			break;
		case 1:
			dev->CPHA = 0;
			dev->CPOL = 1;
			break;
		case 2:
			dev->CPHA = 1;
			dev->CPOL = 0;
			break;
		case 3:
			dev->CPHA = 1;
			dev->CPOL = 1;
			break;
		}
		ret = 0;
	}
	return ret;
}
int frw_spiSetLSBFirst(void* frw_dev, int set){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev){
		dev->LSBFirst = set;
		ret = 0;
	}
	return ret;
}
int frw_spiSetCSHigh(void* frw_dev, int set){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev){
		dev->CSHigh = set;
		ret = 0;
	}
	return ret;
}
int frw_spiSetDelayDeactiveCS(void* frw_dev, int delay){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev){
		dev->CSDelay = delay;
		ret = 0;
	}
	return ret;
}
int frw_spiSetSpeed(void* frw_dev, int speed){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev){
		dev->Speed = speed;
		ret = 0;
	}
	return ret;
}
int frw_spiSetBitWord(void* frw_dev, int bitPerWord){
	FRW_SPI_DEVICE* dev = (FRW_SPI_DEVICE*)frw_dev;
	int ret = -1;
	if(dev){
		dev->BitWord = bitPerWord;
		ret = 0;
	}
	return ret;
}


