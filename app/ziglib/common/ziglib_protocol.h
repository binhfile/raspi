/*
 * ziglib_protocol.h
 *
 *  Created on: Oct 11, 2015
 *      Author: dev
 */

#ifndef COMMON_ZIGLIB_PROTOCOL_H_
#define COMMON_ZIGLIB_PROTOCOL_H_
#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute__((packed)){
	unsigned char	type;
	unsigned char 	srcGroup;
	unsigned char   src;
	unsigned char   payload[1];
}ZIG_PACKET;
typedef struct __attribute__((packed)){

}ZIG_PACKET_COMMAND;

#ifdef __cplusplus
}
#endif

#endif /* COMMON_ZIGLIB_PROTOCOL_H_ */
