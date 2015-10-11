/*
 * ziglib_router_layer.h
 *
 *  Created on: Oct 11, 2015
 *      Author: dev
 */

#ifndef COMMON_ZIGLIB_ROUTER_LAYER_H_
#define COMMON_ZIGLIB_ROUTER_LAYER_H_
#include "ziglib_router_layer_protocol.h"

typedef int (*ZIGLIB_ROUTERLAYER_CALLBACK)(int type, void* obj, void* user);
enum ZIGLIB_ROUTERLAYER_CALLBACK_TYPE{
	ZIGLIB_ROUTERLAYER_CALLBACK_RX,
	ZIGLIB_ROUTERLAYER_CALLBACK_TX,
	ZIGLIB_ROUTERLAYER_CALLBACK_GET_TX_BUFFER
};
typedef struct{
	void* packet;
}ZIGLIB_ROUTERLAYER_CALLBACK_RX_OBJ;

typedef struct{
	ZIGLIB_ROUTERLAYER_CALLBACK		callback;
	void*							user;

	unsigned short network;

	unsigned short parrent;
	unsigned short neighbors[ZIG_ROUTER_LAYER_MAX_NEIGHBOR];
	unsigned char  neighborCount;
}_ZIGLIB_ROUTERLAYER;

void* ziglib_routerLayerAlloc();
int   ziglib_routerLayerFree(void* layer);
int   ziglib_routerLayerSetNetworkAddress(void* layer, unsigned short networkAddress);
int   ziglib_routerLayerSetCallback(void* layer, ZIGLIB_ROUTERLAYER_CALLBACK callback, void* user);
int   ziglib_routerLayerProcessData(void* layer, void* data);
int   ziglib_routerLayerGetTxPayloadBuffer(void* layer);
int   ziglib_routerLayerSend(void* layer,
		void* txBuffer, int payloadLength,
		unsigned char srcGroup, unsigned char srcAddress,
		unsigned char destGroup, unsigned char destAddress);


#endif /* COMMON_ZIGLIB_ROUTER_LAYER_H_ */
