#include "mrf24j40.h"
#include <lib_debug.h>
#include <lib_mem.h>

void* 				mrf24j40_allocDevice(const char* szSpiDeviceName, int resetPinNum, int intrPinNum){
	MRF24J40* dev = (MRF24J40*)lib_alloc(sizeof(MRF24J40));
	int i = 0;
	if(dev){
		dev->szSpiDeviceName = lib_alloc(FRW_SPI_NAME_LEN);
		for(i = 0; i < FRW_SPI_NAME_LEN; i++){
			dev->szSpiDeviceName[i] = szSpiDeviceName[i];
			if(szSpiDeviceName[i] == 0) break;
		}
		dev->resetPinNum = resetPinNum;
		dev->intrPinNum  = intrPinNum;

		dev->access = 0;
		dev->cb = 0;
		dev->cb_obj = 0;
		dev->cmd = 0;
		dev->intr = 0;
		dev->reset = 0;
		dev->txSequence = 0;

		dev->addr16 = 0;
		dev->addr32 = 0;
		dev->panId  = 0;
		dev->channel= 0;
		dev->turboMode = 0;

		dev->access = lib_semAlloc(1);
		dev->cmd    = lib_spiAllocDevice();
		dev->reset  = lib_gpioAllocDevice(dev->resetPinNum);
		dev->intr   = lib_gpioAllocDevice(dev->intrPinNum);
		dev->threadRx = lib_threadAlloc(_mrf24j40_rx_run);
		lib_spiSetDeviceName(dev->cmd, dev->szSpiDeviceName);
	}
	return dev;
}
int   				mrf24j40_freeDevice(void* dev){
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev){
		mrf24j40_closeDevice(_dev);
		lib_semFree(_dev->access);
		lib_gpioFreeDevice(_dev->reset);
		lib_gpioFreeDevice(_dev->intr);
		lib_spiFreeDevice(_dev->cmd);
		lib_threadFree(_dev->threadRx);
		lib_free(_dev, sizeof(MRF24J40));
	}
	return 0;
}

int mrf24j40_openDevice(void* dev){
	int ret = -1;
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		ret = lib_gpioSetDirectory(_dev->reset, 0);
		ret |= lib_gpioWrite(_dev->reset, 0);
		ret |= lib_gpioSetInterrupt(_dev->intr, 1);

		ret |= lib_spiSetOperationMode(_dev->cmd, 0);
		ret |= lib_spiSetSpeed(_dev->cmd, 1000 * 1000);
		ret |= lib_spiSetBitWord(_dev->cmd, 8);
		ret |= lib_spiOpenDevice(_dev->cmd);

		lib_threadStart(_dev->threadRx, dev);
	}
	return ret;
}
int mrf24j40_closeDevice(void* dev){
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		lib_threadStop(_dev->threadRx, 100);
		lib_spiCloseDevice(_dev->cmd);
	}
	return 0;
}
void*				mrf24j40_getTxPayload(void* dev){
	return &(((MAC_TX_DATA_PACKET*)&(((MRF24J40*)dev)->txBuffer[0]))->payload[0]);
}
int mrf24j40_setChannel(void* dev, int channel){
	((MRF24J40*)dev)->channel = channel;
//	return _mrf24j40_writeLongReg(dev, MRF_RFCON0, (((channel - 11) << 4) | 0x03));
	return 0;
}
int mrf24j40_initInterrupt(void* dev){
	// interrupts for rx and tx normal complete
	return _mrf24j40_writeShortReg(dev, MRF_INTCON, 0b11110110);
}
int mrf24j40_setPan(void* dev, unsigned short pan){
//	_mrf24j40_writeShortReg(dev, MRF_PANIDH, pan >> 8);
//	_mrf24j40_writeShortReg(dev, MRF_PANIDL, pan & 0xff);
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		_dev->panId = pan;
	}
	return 0;
}
int mrf24j40_setAddress16(void* dev, unsigned short address){
//	_mrf24j40_writeShortReg(dev, MRF_SADRH, address >> 8);
//	_mrf24j40_writeShortReg(dev, MRF_SADRL, address);
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		_dev->addr16 = address;
	}
	return 0;
}
int mrf24j40_setAddress32(void* dev, unsigned long long address){

//	_mrf24j40_writeShortReg(dev, MRF_EADR0, address);
//	_mrf24j40_writeShortReg(dev, MRF_EADR1, address >> 8);
//	_mrf24j40_writeShortReg(dev, MRF_EADR2, address >> 8*2);
//	_mrf24j40_writeShortReg(dev, MRF_EADR3, address >> 8*3);
//	_mrf24j40_writeShortReg(dev, MRF_EADR4, address >> 8*4);
//	_mrf24j40_writeShortReg(dev, MRF_EADR5, address >> 8*5);
//	_mrf24j40_writeShortReg(dev, MRF_EADR6, address >> 8*6);
//	_mrf24j40_writeShortReg(dev, MRF_EADR7, address >> 8*7);
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		_dev->addr32 = address;
	}
	return 0;
}
int mrf24j40_softReset(void* dev){
	_mrf24j40_writeShort(dev, MRF_SOFTRST, 0x07);
	lib_sleepMs(100);
	return 0;
}
int mrf24j40_initDevice(void* dev){
	unsigned char val;
	mrf24j40_hardReset(dev);
	mrf24j40_softReset(dev);
	_mrf24j40_writeShort(dev, MRF_RXFLUSH, 0x01);

	_mrf24j40_writeShortReg(dev, MRF_SADRH, ((MRF24J40*)dev)->addr16 >> 8);
	_mrf24j40_writeShortReg(dev, MRF_SADRL, ((MRF24J40*)dev)->addr16);
	_mrf24j40_writeShortReg(dev, MRF_EADR0, ((MRF24J40*)dev)->addr32);
	_mrf24j40_writeShortReg(dev, MRF_EADR1, ((MRF24J40*)dev)->addr32 >> 8);
	_mrf24j40_writeShortReg(dev, MRF_EADR2, ((MRF24J40*)dev)->addr32 >> 8*2);
	_mrf24j40_writeShortReg(dev, MRF_EADR3, ((MRF24J40*)dev)->addr32 >> 8*3);
	_mrf24j40_writeShortReg(dev, MRF_EADR4, ((MRF24J40*)dev)->addr32 >> 8*4);
	_mrf24j40_writeShortReg(dev, MRF_EADR5, ((MRF24J40*)dev)->addr32 >> 8*5);
	_mrf24j40_writeShortReg(dev, MRF_EADR6, ((MRF24J40*)dev)->addr32 >> 8*6);
	_mrf24j40_writeShortReg(dev, MRF_EADR7, ((MRF24J40*)dev)->addr32 >> 8*7);
	_mrf24j40_writeShortReg(dev, MRF_PANIDH, ((MRF24J40*)dev)->panId >> 8);
	_mrf24j40_writeShortReg(dev, MRF_PANIDL, ((MRF24J40*)dev)->panId & 0xff);

    _mrf24j40_writeLongReg(dev, MRF_RFCON0, 0x03); // recommended from datasheet
    _mrf24j40_writeLongReg(dev, MRF_RFCON1, 0x02); // recommended from datasheet
    _mrf24j40_writeLongReg(dev, MRF_RFCON2, 0x80); // Enable PLL
    _mrf24j40_writeLongReg(dev, MRF_RFCON3, 0x00); // TX Power = 0dB
    /** TX Filter Control enable
     *  Recovery from Sleep less than 1ms
     *  Battery Minitor disable
     */ 
    _mrf24j40_writeLongReg(dev, MRF_RFCON6, 0x90);
    _mrf24j40_writeLongReg(dev, MRF_RFCON7, 0x80); // Sleep clock use 100kHz internal osc
    _mrf24j40_writeLongReg(dev, MRF_RFCON8, 0x10); // VCO Control, recommended from datasheet
    /** CLKOUT pin disable
     *  Sleep clock divided = 2^1
     */ 
    _mrf24j40_writeLongReg(dev, MRF_SLPCON1, 0x21);// 0x01

    //  Configuration for nonbeacon-enabled devices (see Section 3.8 “Beacon-Enabled and
    //  Nonbeacon-Enabled Networks”):
    /** Carrier sense only
     *  CCA-CS recommended
     */ 
    _mrf24j40_writeShortReg(dev, MRF_BBREG2, 0x80);
    /** Energy detection threshold for CCA, recommended
     */ 
    _mrf24j40_writeShortReg(dev, MRF_CCAEDTH, 0x60);
    _mrf24j40_writeShort(dev, MRF_BBREG6, 0x40); // – Set appended RSSI value to RXFIFO.
    /** FIFO enable
     *  
     */ 
    _mrf24j40_writeShortReg(dev, MRF_PACON2, 0x98);
    _mrf24j40_writeShortReg(dev, MRF_TXSTBL, 0x95); // recommended
    do{
    	val = _mrf24j40_readLong(dev, MRF_RFSTATE);
    	lib_sleepMs(50);
    }while((val & 0xA0) != 0xA0);// wait RX state
    mrf24j40_initInterrupt(dev);
    _mrf24j40_writeLongReg(dev, MRF_RFCON0, 0x03);
    _mrf24j40_writeLongReg(dev, MRF_RFCON1, 0x02);

    _mrf24j40_writeLongReg(dev, MRF_RFCON0, (((((MRF24J40*)dev)->channel - 11) << 4) | 0x03));
    // max power is by default.. just leave it...
	if(((MRF24J40*)dev)->turboMode){
		_mrf24j40_writeShortReg(dev, MRF_BBREG0, 0x01);
		val = _mrf24j40_readShort(dev, MRF_BBREG3);
		val &= ~(0b11110000);
		val |= 0b00110000;
		_mrf24j40_writeShortReg(dev, MRF_BBREG3, val);
		val = _mrf24j40_readShort(dev, MRF_BBREG4);
		val &= ~(0b11100000);
		val |= 0b01000000;
		_mrf24j40_writeShortReg(dev, MRF_BBREG4, val);
		_mrf24j40_writeShort(dev, MRF_SOFTRST, 0b00000010);
	}else{
		_mrf24j40_writeShortReg(dev, MRF_BBREG0, 0x00);
		val = _mrf24j40_readShort(dev, MRF_BBREG3);
		val &= ~(0b11110000);
		val |= 0b11010000;
		_mrf24j40_writeShortReg(dev, MRF_BBREG3, val);
		val = _mrf24j40_readShort(dev, MRF_BBREG4);
		val &= ~(0b11100000);
		val |= 0b10000000;
		_mrf24j40_writeShortReg(dev, MRF_BBREG4, val);
		_mrf24j40_writeShort(dev, MRF_SOFTRST, 0b00000010);
	}
    // Set transmitter power - See “REGISTER 2-62: RF CONTROL 3 REGISTER (ADDRESS: 0x203)”.
    _mrf24j40_writeShortReg(dev, MRF_RFCTL, 0x04); //  reset RF state machine
    _mrf24j40_writeShortReg(dev, MRF_RFCTL, 0x00); //  out of reset
    lib_sleepMs(10); // delay at least 192usec
	return 0;
}
unsigned char		mrf24j40_calcRSSI(void* dev){
	unsigned char rssi = 0;
	_mrf24j40_writeShort(dev, MRF_BBREG6, 0x80);
	do{
		rssi = _mrf24j40_readShort(dev, MRF_BBREG6);
		lib_sleepMs(1);
	}while((rssi & 0x01) != 0x01);
	rssi = _mrf24j40_readLong(dev, MRF_RSSI);
	_mrf24j40_writeShort(dev, MRF_BBREG6, 0x40);
	return rssi;

}
unsigned short mrf24j40_getPan(void* dev){
    unsigned char panh = _mrf24j40_readShort(dev, MRF_PANIDH);
    return ((unsigned short)panh << 8) | (unsigned short)_mrf24j40_readShort(dev, MRF_PANIDL);
}
unsigned short mrf24j40_getAddress16(void* dev){
    unsigned short a16h = _mrf24j40_readShort(dev, MRF_SADRH);
    return ((unsigned short)a16h << 8) | (unsigned short)_mrf24j40_readShort(dev, MRF_SADRL);
}
int mrf24j40_sendDataPacket16(void* dev,
		int payloadLen,
		unsigned short destPan, unsigned short destAddr,
		int ackRequest, int securityEnable, int framePending, int intraPan){

    int 				addr, i;
    MRF24J40			*_dev;;
    MAC_TX_DATA_PACKET 	*pkt;

    addr = MRF_TX_FIFO;
    _dev = (MRF24J40*)dev;
    pkt = (MAC_TX_DATA_PACKET*)_dev->txBuffer;
    if(_dev){
		// init packet
		if(payloadLen < 0) payloadLen = 0;
		if(payloadLen > MAC_DATA_PAYLOAD_SIZE) payloadLen = MAC_DATA_PAYLOAD_SIZE;
		pkt->headerLen	=	sizeof(MAC_HEADER);
		pkt->frameLen	=   sizeof(MAC_HEADER) + payloadLen;
		pkt->header.ctrl.type 			= MAC_FRAME_TYPE_DATA;
		pkt->header.ctrl.security 		= securityEnable ? 1 : 0;
		pkt->header.ctrl.framePending 	= framePending ? 1 : 0;
		pkt->header.ctrl.ackReq 		= ackRequest ? 1 : 0;
		pkt->header.ctrl.intraPAN		= intraPan ? 1 : 0;
		pkt->header.ctrl.destAddrMode	= MAC_ADDRESS_MODE_16;
		pkt->header.ctrl.srcAddrMode	= MAC_ADDRESS_MODE_16;
		pkt->header.seq					= _dev->txSequence++;
		pkt->header.destPAN				= destPan;
		pkt->header.destAddr			= destAddr;
		pkt->header.srcPAN				= _dev->panId;
		pkt->header.srcAddr				= _dev->addr16;
		lib_semPend(_dev->access, 0);
		for(i = 0; i < pkt->frameLen + 2; i++){
			_mrf24j40_writeLong(dev, addr++, _dev->txBuffer[i]);
		}
		_mrf24j40_writeShort(dev, MRF_TXNCON, ((ackRequest ? 1 : 0)<<MRF_TXNACKREQ | 1<<MRF_TXNTRIG));
		lib_semPost(_dev->access);
//		DUMP(pkt.payload, payloadLen, "%d --> %d", pkt.header.srcAddr, pkt.header.destAddr);
    }
    return 0;
}
int mrf24j40_setCallback(void* dev, MRF24J40_CALLBACK fxn, void* obj){
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		_dev->cb = fxn;
		_dev->cb_obj = obj;
	}
	return 0;
}
inline void _mrf24j40_writeShort(void* dev, unsigned char address, unsigned char data){
	static unsigned char tx[2];
	static unsigned char rx[2];
	tx[0] = ((address << 1) & 0b01111110) | 0x01;
	tx[1] = data;
	lib_spiTransfer(((MRF24J40*)dev)->cmd, tx, rx, 2);
}
inline void _mrf24j40_writeLong(void* dev, unsigned short address, unsigned char data){
	static unsigned char tx[3];
	static unsigned char rx[3];

	tx[0] = 0x80 | ((address >> 3) & 0x7F);
	tx[1] = 0x10 | ((address << 5) & 0xE0);
	tx[2] = data;
	lib_spiTransfer(((MRF24J40*)dev)->cmd, tx, rx, 3);
}
unsigned char _mrf24j40_readShort(void* dev, unsigned char address){
	unsigned char tx[2];
	unsigned char rx[2];
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		tx[0] = (address << 1 & 0b01111110);
		rx[1] = 0;
		lib_spiTransfer(_dev->cmd, tx, rx, 2);
	}
	return rx[1];
}
unsigned char _mrf24j40_readLong(void* dev, unsigned short address){
	unsigned char tx[3];
	unsigned char rx[3];
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		tx[0] = 0x80 | ((address >> 3) & 0x7F);
		tx[1] = 0x00 | ((address << 5) & 0xE0);
		rx[2] = 0;
		lib_spiTransfer(_dev->cmd, tx, rx, 3);
	}
	return rx[2];
}
int _mrf24j40_writeShortReg(void* dev, unsigned char address, unsigned char data){
	int ret = -1;
	_mrf24j40_writeShort(dev, address, data);
	unsigned char fb = _mrf24j40_readShort(dev, address);
	if(data == fb){
		ret = 0;
	}else{
		LREP("write reg 0x%02X=0x%02X failed, fb=0x%02X.\n",
				address, data, fb);
	}
	return ret;
}
int _mrf24j40_writeLongReg(void* dev, unsigned short address, unsigned char data){
	int ret = -1;
	unsigned char fb;
	_mrf24j40_writeLong(dev, address, data);
	fb = _mrf24j40_readLong(dev, address);
	if(data == fb){
		ret = 0;
	}else{
		LREP("write reg 0x%04X=0x%02X failed, fb=0x%02X.\n",
				address, data, fb);
	}
	return ret;
}
int mrf24j40_setTurboMode(void* dev, int set){
	((MRF24J40*)dev)->turboMode = set;
	return 0;
//	int ret = -1;
//	unsigned char val;
//	if(set){
//		_mrf24j40_writeShortReg(dev, MRF_BBREG0, 0x01);
//		val = _mrf24j40_readShort(dev, MRF_BBREG3);
//		val &= ~(0b11110000);
//		val |= 0b00110000;
//		_mrf24j40_writeShortReg(dev, MRF_BBREG3, val);
//		val = _mrf24j40_readShort(dev, MRF_BBREG4);
//		val &= ~(0b11100000);
//		val |= 0b01000000;
//		_mrf24j40_writeShortReg(dev, MRF_BBREG4, val);
//		_mrf24j40_writeShort(dev, MRF_SOFTRST, 0b00000010);
//	}else{
//		_mrf24j40_writeShortReg(dev, MRF_BBREG0, 0x00);
//		val = _mrf24j40_readShort(dev, MRF_BBREG3);
//		val &= ~(0b11110000);
//		val |= 0b11010000;
//		_mrf24j40_writeShortReg(dev, MRF_BBREG3, val);
//		val = _mrf24j40_readShort(dev, MRF_BBREG4);
//		val &= ~(0b11100000);
//		val |= 0b10000000;
//		_mrf24j40_writeShortReg(dev, MRF_BBREG4, val);
//		_mrf24j40_writeShort(dev, MRF_SOFTRST, 0b00000010);
//	}
//	return ret;
}
int mrf24j40_hardReset(void* dev){
	MRF24J40* _dev = (MRF24J40*)dev;
	if(_dev)
	{
		lib_gpioWrite(_dev->reset, 0);
		lib_sleepMs(10);
		lib_gpioWrite(_dev->reset, 1);
		lib_sleepMs(20);
	}
	return 0;
}
void _mrf24j40_rx_run(void* obj, int* terminate){
	MRF24J40* inst = (MRF24J40*)obj;
	int ret, i;
	unsigned char headerLen = sizeof(MAC_HEADER);
	MRF24J40_CALLBACK_RX_PARAM rxParam;
	unsigned char intstats, txstats, frameLen;
	rxParam.packet = inst->rxBuffer;
	LREP("interrupt routine is running.\n");
	while((*terminate) == 0){
		ret = lib_gpioWaitEvent(inst->intr, 500);
		if(ret < 0){
			LREP("wait intr failed.\n");
			break;
		}else if(ret > 0){
			lib_semPend(inst->access, 0);
			intstats = _mrf24j40_readShort(inst, MRF_INTSTAT);
			lib_semPost(inst->access);
			//LREP("intr detected %02x.\n", intstats);
			if(intstats & 0x01){
				lib_semPend(inst->access, 0);
				txstats = _mrf24j40_readShort(inst, MRF_TXSTAT);
				lib_semPost(inst->access);
				//LREP("txstats %02x.\n", txstats);
				if(txstats & 0x01){
					LREP("TX normal failed, retries=%d\n", ((txstats & 0b11000000) >> 6));
				}else{
//					LREP("TX normal success\n");
					if(inst->cb){
						inst->cb(MRF24J40_CALLBACK_TYPE_TX_DONE, &rxParam, inst->cb_obj);
					}
				}
			}
			if(intstats & 0b00001000){
//				LREP("RX fifo interrupt\n");
				lib_semPend(inst->access, 0);
				_mrf24j40_writeShort(inst, MRF_BBREG1, 0x04);// disable rx
				frameLen = _mrf24j40_readLong(inst, 0x300);
				frameLen = frameLen + 3;
				if(frameLen > MRF_RX_FIFO_LEN)
					frameLen = MRF_RX_FIFO_LEN;

				for(i = 0; i < frameLen; i++){
					inst->rxBuffer[i] = _mrf24j40_readLong(inst, 0x300 + i);
				}
				_mrf24j40_writeShort(inst, MRF_BBREG1, 0x00);// enable rx
				lib_semPost(inst->access);
				rxParam.length = frameLen;
				if(inst->cb){
					inst->cb(MRF24J40_CALLBACK_TYPE_RX, &rxParam, inst->cb_obj);
				}
			}
		}
	}
	LREP("interrupt routine is stopped.\n");
}
