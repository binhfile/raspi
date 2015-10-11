/*
 * ieee802154_mac.h
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */

#ifndef LIB_DRIVERS_MRF24J40_IEEE802154_MAC_H_
#define LIB_DRIVERS_MRF24J40_IEEE802154_MAC_H_
#ifdef __cplusplus
extern "C" {
#endif
typedef struct __attribute__((packed)) {
	unsigned char type 			: 3;
	unsigned char security		: 1;
	unsigned char framePending	: 1;
	unsigned char ackReq		: 1;
	unsigned char intraPAN		: 1;
	unsigned char rsv1 			: 3;
	unsigned char destAddrMode	: 2;
	unsigned char rsv2			: 2;
	unsigned char srcAddrMode	: 2;

}MAC_HEADER_CTRL;
typedef struct __attribute__((packed)) {
	MAC_HEADER_CTRL ctrl;
	unsigned char 	seq;
	unsigned short	destPAN;
	unsigned short	destAddr;
	unsigned short	srcPAN;
	unsigned short	srcAddr;
}MAC_HEADER;
#define MAC_DATA_PAYLOAD_SIZE		(144 - 11 - 2)
typedef struct __attribute__((packed)) {
	unsigned char   headerLen;						// header len
	unsigned char 	frameLen;						// header_len + payload_len
	MAC_HEADER 		header;
	unsigned char   payload[MAC_DATA_PAYLOAD_SIZE];
}MAC_TX_DATA_PACKET;
typedef struct __attribute__((packed)) {
	unsigned char 	frameLen;						// header_len + payload_len + fcs_len(2)
	MAC_HEADER 		header;
	unsigned char   payload[MAC_DATA_PAYLOAD_SIZE];
	unsigned short  fcs;
	unsigned char   lqi;
	unsigned char   rssi;
}MAC_RX_DATA_PACKET;
enum MAC_FRAME_TYPE{
	MAC_FRAME_TYPE_DATA = 0b00000001,
};
enum MAC_ADDRESS_MODE{
	MAC_ADDRESS_MODE_16 = 0b00000010,
};



#ifdef __cplusplus
}
#endif
#endif /* LIB_DRIVERS_MRF24J40_IEEE802154_MAC_H_ */
