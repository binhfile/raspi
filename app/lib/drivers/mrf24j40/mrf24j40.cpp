#include "mrf24j40.h"
#include <lib_debug.h>
// essential for obtaining the data frame only
// bytes_MHR = 2 Frame control + 1 sequence number + 2 panid + 2 shortAddr Destination + 2 shortAddr Source
static int bytes_MHR = 9;
static int bytes_FCS = 2; // FCS length = 2
static int bytes_nodata = bytes_MHR + bytes_FCS; // no_data bytes in PHY payload,  header length + FCS

static int ignoreBytes = 0; // bytes to ignore, some modules behaviour.

using namespace driver;
MRF24J40::MRF24J40(std::string szCmdDevice,
		 int resetGpioNum,
		 int intrGpioNum){
	m_reset = lib_gpioAllocDevice(resetGpioNum);
	m_intr 	= lib_gpioAllocDevice(intrGpioNum);
	m_cmd 	= lib_spiAllocDevice();
	m_interrupt = new lib::platform::Thread(interrupt_run);

	lib_spiSetDeviceName(m_cmd, szCmdDevice.c_str());
}
MRF24J40::~MRF24J40(){
	m_interrupt->stop(100);

	lib_gpioFreeDevice(m_reset);
	lib_gpioFreeDevice(m_intr);
	delete m_interrupt;
}
int MRF24J40::openDevice(){
	int ret = -1;
	ret = lib_gpioSetDirectory(m_reset, 0);
	ret |= lib_gpioWrite(m_reset, 0);
	ret |= lib_gpioSetInterrupt(m_intr, 3);

	ret |= lib_spiSetOperationMode(m_cmd, 0);
	ret |= lib_spiSetSpeed(m_cmd, 1000 * 1000);
	ret |= lib_spiSetBitWord(m_cmd, 8);
	ret |= lib_spiOpenDevice(m_cmd);
	if(ret == 0)
		m_interrupt->start(this);
	return ret;
}
int MRF24J40::closeDevice(){
	m_interrupt->stop(100);
	lib_spiCloseDevice(m_cmd);
	return 0;
}
int MRF24J40::setChannel(int channel){
	return writeLongReg(MRF_RFCON0, (((channel - 11) << 4) | 0x03));
}
int MRF24J40::initInterrupt(){
	// interrupts for rx and tx normal complete
	return writeShortReg(MRF_INTCON, 0b11110110);
}
int MRF24J40::setPan(unsigned short pan){
	writeShortReg(MRF_PANIDH, pan >> 8);
	writeShortReg(MRF_PANIDL, pan & 0xff);
	return 0;
}
int MRF24J40::setAddress16(unsigned short address){
	writeShortReg(MRF_SADRH, address >> 8);
	writeShortReg(MRF_SADRL, address & 0xff);
	return 0;
}
int MRF24J40::initDevice(){
	hardReset();
	writeShortReg(MRF_PACON2, 0x98); // – Initialize FIFOEN = 1 and TXONTS = 0x6.
    writeShortReg(MRF_TXSTBL, 0x95); // – Initialize RFSTBL = 0x9.

    writeLongReg(MRF_RFCON0, 0x03); // – Initialize RFOPT = 0x03.
    writeLongReg(MRF_RFCON1, 0x01); // – Initialize VCOOPT = 0x02.
    writeLongReg(MRF_RFCON2, 0x80); // – Enable PLL (PLLEN = 1).
    writeLongReg(MRF_RFCON6, 0x90); // – Initialize TXFIL = 1 and 20MRECVR = 1.
    writeLongReg(MRF_RFCON7, 0x80); // – Initialize SLPCLKSEL = 0x2 (100 kHz Internal oscillator).
    writeLongReg(MRF_RFCON8, 0x10); // – Initialize RFVCO = 1.
    writeLongReg(MRF_SLPCON1, 0x21); // – Initialize CLKOUTEN = 1 and SLPCLKDIV = 0x01.

    //  Configuration for nonbeacon-enabled devices (see Section 3.8 “Beacon-Enabled and
    //  Nonbeacon-Enabled Networks”):
    writeShortReg(MRF_BBREG2, 0x80); // Set CCA mode to ED
    writeShortReg(MRF_CCAEDTH, 0x60); // – Set CCA ED threshold.
    writeShortReg(MRF_BBREG6, 0x41); // – Set appended RSSI value to RXFIFO.
    initInterrupt();
    setChannel(12);
    // max power is by default.. just leave it...
    // Set transmitter power - See “REGISTER 2-62: RF CONTROL 3 REGISTER (ADDRESS: 0x203)”.
    writeShortReg(MRF_RFCTL, 0x04); //  – Reset RF state machine.
    writeShortReg(MRF_RFCTL, 0x00); // part 2
    lib::platform::Thread::sleepMs(1); // delay at least 192usec
	return 0;
}
unsigned short MRF24J40::getPan(){
    unsigned char panh = readShort(MRF_PANIDH);
    return ((unsigned short)panh << 8) | (unsigned short)readShort(MRF_PANIDL);
}
unsigned short MRF24J40::getAddress16(){
    unsigned short a16h = readShort(MRF_SADRH);
    return ((unsigned short)a16h << 8) | (unsigned short)readShort(MRF_SADRL);
}
int MRF24J40::sendData(unsigned short address, const void* data, int length){
	unsigned char *p = (unsigned char*)data;
    int i = 0;
    static unsigned char s_seq = 1;
    writeLong(i++, bytes_MHR); // header length
    // +ignoreBytes is because some module seems to ignore 2 bytes after the header?!.
    // default: ignoreBytes = 0;
    writeLong(i++, bytes_MHR+ignoreBytes+length);

    // 0 | pan compression | ack | no security | no data pending | data frame[3 bits]
    writeLong(i++, 0b01100001); // first byte of Frame Control
    // 16 bit source, 802.15.4 (2003), 16 bit dest,
    writeLong(i++, 0b10001000); // second byte of frame control
    writeLong(i++, s_seq++);  // sequence number 1

    unsigned short panid = getPan();

    writeLong(i++, panid & 0xff);  // dest panid
    writeLong(i++, panid >> 8);
    writeLong(i++, address & 0xff);  // dest16 low
    writeLong(i++, address >> 8); // dest16 high

    unsigned short src16 = getAddress16();
    writeLong(i++, src16 & 0xff); // src16 low
    writeLong(i++, src16 >> 8); // src16 high

    // All testing seems to indicate that the next two bytes are ignored.
    //2 bytes on FCS appended by TXMAC
    i+=ignoreBytes;
    for (int q = 0; q < length; q++) {
    	writeLong(i++, p[q]);
    }
    // ack on, and go!
    writeShort(MRF_TXNCON, (1<<MRF_TXNACKREQ | 1<<MRF_TXNTRIG));
}
void MRF24J40::writeShort(unsigned char address, unsigned char data){
	unsigned char tx[2];
	unsigned char rx[2];

	tx[0] = (address << 1 & 0b01111110) | 0x01;
	tx[1] = data;
	lib_spiTransfer(m_cmd, tx, rx, 2);
}
void MRF24J40::writeLong(unsigned short address, unsigned char data){
	unsigned char tx[3];
	unsigned char rx[3];

	tx[0] = 0x80 | (address >> 3);
	tx[1] = 0x10 | (address << 5);
	tx[2] = data;
	lib_spiTransfer(m_cmd, tx, rx, 3);
}
unsigned char MRF24J40::readShort(unsigned char address){
	unsigned char tx[2];
	unsigned char rx[2];

	tx[0] = (address << 1 & 0b01111110);
	rx[1] = 0;
	lib_spiTransfer(m_cmd, tx, rx, 2);
	return rx[1];
}
unsigned char MRF24J40::readLong(unsigned short address){
	unsigned char tx[3];
	unsigned char rx[3];

	tx[0] = 0x80 | (address >> 3);
	tx[1] = 0x00 | (address << 5);
	rx[2] = 0;
	lib_spiTransfer(m_cmd, tx, rx, 3);
	return rx[2];
}
int MRF24J40::writeShortReg(unsigned char address, unsigned char data){
	int ret = -1;
	writeShort(address, data);
	unsigned char fb = readShort(address);
	if(data == fb){
		ret = 0;
	}else{
		LREP("write reg 0x%02X=0x%02X failed, fb=0x%02X.\n",
				address, data, fb);
	}
	return ret;
}
int MRF24J40::writeLongReg(unsigned short address, unsigned char data){
	int ret = -1;
	writeLong(address, data);
	unsigned char fb = readLong(address);
	if(data == fb){
		ret = 0;
	}else{
		LREP("write reg 0x%04X=0x%02X failed, fb=0x%02X.\n",
				address, data, fb);
	}
	return ret;
}
void MRF24J40::hardReset(){
	lib_gpioWrite(m_reset, 0);
	lib::platform::Thread::sleepMs(10);
	lib_gpioWrite(m_reset, 1);
	lib::platform::Thread::sleepMs(20);
}
void MRF24J40::interrupt_run(void* obj, bool* terminate){
	MRF24J40* inst = (MRF24J40*)obj;
	int ret;
	LREP("interrupt routine is running.\n");
	while(!(*terminate)){
		ret = lib_gpioWaitEvent(inst->m_intr, 500);
		if(ret < 0){
			LREP("wait intr failed.\n");
			break;
		}else if(ret > 0){
			unsigned char stats = inst->readLong(MRF_INTSTAT);

			LREP("intr detected %02x.\n", stats);
		}
	}
	LREP("interrupt routine is stopped.\n");
}
