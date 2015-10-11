/*
 * ziglib_router_layer_protocol.h
 *
 *  Created on: Oct 11, 2015
 *      Author: dev
 */

#ifndef COMMON_ZIGLIB_ROUTER_LAYER_PROTOCOL_H_
#define COMMON_ZIGLIB_ROUTER_LAYER_PROTOCOL_H_
#ifdef __cplusplus
extern "C" {
#endif

#define ZIG_ROUTER_LAYER_MAX_NEIGHBOR	10

typedef struct __attribute__((packed)){
	unsigned short src;
	unsigned short dest;
	unsigned char  hops;
}ZIG_ROUTER_LAYER_PACKET_HEADER;
typedef struct __attribute__((packed)){
	ZIG_ROUTER_LAYER_PACKET_HEADER 		hdr;
	unsigned char						payload[1];
}ZIG_ROUTER_LAYER_PACKET;

#ifdef __cplusplus
}
#endif
#endif /* COMMON_ZIGLIB_ROUTER_LAYER_PROTOCOL_H_ */
