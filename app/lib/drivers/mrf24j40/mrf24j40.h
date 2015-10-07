#ifndef MRF24J40_H__
#define MRF24J40_H__
#include <lib_gpio.h>
#include <lib_spi.h>
#include <lib_sem.h>
#include <lib_thread.h>
#include "ieee802154_mac.h"
#include "mrf24j40_internal.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef int (*MRF24J40_CALLBACK)(int type, void* param, void* obj);
enum MRF24J40_CALLBACK_TYPE{
	MRF24J40_CALLBACK_TYPE_RX = 1,
};
typedef struct{
	void* packet;
	int   length;
}MRF24J40_CALLBACK_RX_PARAM;
typedef struct{
	MRF24J40_CALLBACK	cb;
	void*				cb_obj;

	char szSpiDeviceName[512];
	int	 resetPinNum;
	int  intrPinNum;

	void* reset;
	void* intr;
	void* cmd;
	void* access;
	void* threadRx;

	int  txSequence;

	unsigned short panId;
	unsigned short addr16;


}MRF24J40;

void* 				mrf24j40_allocDevice(const char* szSpiDeviceName, int resetPinNum, int intrPinNum);
int   				mrf24j40_freeDevice(void* dev);
int   				mrf24j40_openDevice(void* dev);
int   				mrf24j40_closeDevice(void* dev);
int	  				mrf24j40_initDevice(void* dev);

int   				mrf24j40_setCallback(void* dev, MRF24J40_CALLBACK fxn, void* obj);
int	  				mrf24j40_setChannel(void* dev, int channel);
int	  				mrf24j40_setPan(void* dev, unsigned short pan);
int	  				mrf24j40_setAddress16(void* dev, unsigned short address);
int	  				mrf24j40_setTurboMode(void* dev, int set);

unsigned short	  	mrf24j40_getPan(void* dev);
unsigned short    	mrf24j40_getAddress16(void* dev);

int   				mrf24j40_sendDataPacket16(void* dev, const void* payload, int payloadLen,
								unsigned short destPan, unsigned short destAddr,
								int ackRequest, int securityEnable, int framePending, int intraPan);
int   				mrf24j40_hardReset(void* dev);
int   				mrf24j40_softReset(void* dev);

void			_mrf24j40_writeShort(void* dev, unsigned char address, unsigned char data);
void 			_mrf24j40_writeLong(void* dev, unsigned short address, unsigned char data);
unsigned char 	_mrf24j40_readShort(void* dev, unsigned char address);
unsigned char 	_mrf24j40_readLong(void* dev, unsigned short address);
int 			_mrf24j40_writeShortReg(void* dev, unsigned char address, unsigned char data);
int 			_mrf24j40_writeLongReg(void* dev, unsigned short address, unsigned char data);
int 			_mrf24j40_initInterrupt(void* dev);
void 			_mrf24j40_rx_run(void* obj, int* terminate);
#ifdef __cplusplus
}
#endif
#endif
