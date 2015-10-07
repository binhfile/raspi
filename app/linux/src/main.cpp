#include <stdio.h>
#include <stdlib.h>
#include <lib_debug.h>
#include <mrf24j40.h>
#include <iostream>
#include <string.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
volatile int 	s_optMode = 0;	// none
void* 			s_semTx = 0;
unsigned char	s_txBuffer[512];
int  			s_txLength = 0;
unsigned short  s_txDestId = 0;

void*			s_semRx;
unsigned char  	s_rxBuffer[512];
unsigned char   s_rxLength = 0;
int mac_callback(int type, void* param, void* obj);
void tx_thread(void* obj, int* terminate);
uint32_t GetCurrentMs()
{
    uint32_t ret = 0;
    struct timeb tv;
    ftime(&tv);
    ret = (uint32_t)(tv.time * 1000 + tv.millitm);
    return ret;
}
int main(int argc, char** argv){
	void* txThread = 0;
	if(argc < 6){
		LREP("usage: %s /dev/spidevX.Y resetPin intrPin id channel\n", argv[0]);
		return 0;
	}
	std::string sz = std::string(argv[1]);
	int resetPin = atoi(argv[2]);
	int intrPin = atoi(argv[3]);
	unsigned short id  = atoi(argv[4]);
	unsigned short channel  = atoi(argv[5]);

	LREP("cmd='%s'\nreset=%d\nintr=%d id=0x%04X channel=%d\n", sz.c_str(), resetPin, intrPin, id, channel);

	s_semTx = lib_semAlloc(0);
	s_semRx = lib_semAlloc(0);
	txThread = lib_threadAlloc(tx_thread);

	void* mrf = mrf24j40_allocDevice(sz.c_str(),
			resetPin,
			intrPin);
	if(mrf24j40_openDevice(mrf) != 0){
		LREP("open device failed.\n");
		mrf24j40_freeDevice(mrf);
		return 0;
	}
	LREP("open done\n");
	mrf24j40_initDevice(mrf);
	mrf24j40_setPan(mrf, 0xcafe);
	mrf24j40_setAddress16(mrf, id);
	mrf24j40_setChannel(mrf, channel);
	mrf24j40_setCallback(mrf, mac_callback, mrf);
	mrf24j40_setTurboMode(mrf, 1);
	lib_threadStart(txThread, mrf);

	while(1){
		std::cout<<">";
		std::cin>>sz;
		if(sz == "q") break;
		else if(sz == "s"){
			std::cout<<"id  >";
			std::cin>>sz;
			unsigned short destid = atoi(sz.c_str());
			std::cout<<"send>";
			std::cin>>sz;
			mrf24j40_sendDataPacket16(mrf, sz.c_str(), sz.length(),
					0xcafe, destid, 1, 0, 0, 0);
		}
		else if(sz == "i"){
			mrf24j40_initDevice(mrf);
		}
		else if(sz == "r"){
			LREP("goto rx mode.\n");
			s_optMode = 1;
		}
		else if(sz == "t"){
			LREP("goto tx mode.\n");
			std::cout<<"dest id>";
			std::cin>>sz;
			unsigned short destid = atoi(sz.c_str());
			std::cout<<"payload len>";
			std::cin>>sz;
			int payloadLen = atoi(sz.c_str());
			if(payloadLen > MAC_DATA_PAYLOAD_SIZE) payloadLen = MAC_DATA_PAYLOAD_SIZE;
			std::cout<<"packet count>";
			std::cin>>sz;
			int pktCount = atoi(sz.c_str());
			LREP("tx to %d payload len = %d packet count = %d\n", destid, payloadLen, pktCount);
			unsigned char cnt = 0;
			unsigned char payload[512];
			int ret;
			s_optMode = 2;
			int i;
			int failedCnt = 0;
			int passedCnt = 0;
			int totalBytes = 0;
			unsigned int timeNow, timeEnd;
			timeNow = GetCurrentMs();
			int retries = 0;
			for(i = 0; i < pktCount; i++){
				for(int j = 0; j < payloadLen; j++){
					payload[j] = cnt++;
				}
				//LREP("send pkt %d ...", i + 1);
				mrf24j40_sendDataPacket16(mrf, payload, payloadLen,
						0xcafe, destid, 1, 0, 0, 0);
				ret = lib_semPend(s_semRx, 1000);
				int err = 1;
				if(ret <= 0){
					LREP("not rx\n");
					//i --;
					//retries++;
					//if(retries > 3){
					//	LREP(" retries failed.\n");
					//	break;
					//}
				}else{
					int passed = 1;
					if(s_rxLength != payloadLen) passed = 0;
					for(int j = 0; j < payloadLen; j++){
						if(s_rxBuffer[j] != payload[j]){
							passed = 0;
							break;
						}
					}
					if(!passed){
						LREP("not match.\n");
						DUMP(payload, payloadLen, "tx %d bytes", payloadLen);
						DUMP(s_rxBuffer, s_rxLength, "rx %d bytes", s_rxLength);
					}else{
						retries = 0;
//						LREP("OK\n");
						totalBytes += payloadLen;
						err = 0;
					}
				}
				if(err){
					failedCnt ++;
				}else{
					passedCnt ++;
				}
			}
			timeEnd = GetCurrentMs();
			unsigned int timeDiff = timeEnd - timeNow;
			float speed;
			if(timeDiff > 0){
				speed = (float)totalBytes * 8000.0f / timeDiff;
			}
			LREP("DONE PASSED %d FAILED %d SPEED %.2f (%.2f Kib/s)\n", passedCnt, failedCnt, speed, speed/1024);
		}
	}
	lib_threadStop(txThread, 1000);
	mrf24j40_freeDevice(mrf);
	lib_semPost(s_semTx);
	lib_semPost(s_semRx);
	lib_semFree(s_semTx);
	lib_semFree(s_semRx);
	LREP("QUIT.\n");
	return 0;
}
int mac_callback(int type, void* param, void* obj){
	if(type == MRF24J40_CALLBACK_TYPE_RX){
		MRF24J40_CALLBACK_RX_PARAM* rx = (MRF24J40_CALLBACK_RX_PARAM*)param;
		MAC_RX_DATA_PACKET* pkt = (MAC_RX_DATA_PACKET*) rx->packet;
		int frameLen = pkt->frameLen;
		int payloadLen = frameLen - 2 - sizeof(MAC_HEADER);
		if(frameLen < 0) frameLen = 0;
		if(frameLen > 256) frameLen = 256;
		if(payloadLen < 0) payloadLen = 0;
		if(payloadLen > 256) payloadLen = 256;
//		LREP("rx %d bytes\n", rx->length);
//		DUMP(&pkt->header, sizeof(MAC_HEADER), "header %d bytes", sizeof(MAC_HEADER));
		//DUMP(pkt->payload, payloadLen, "%d --> rx %d bytes",pkt->header.srcAddr, payloadLen);

		if(s_optMode == 1){
			memcpy(s_txBuffer, pkt->payload, payloadLen);
			s_txLength = payloadLen;
			s_txDestId = pkt->header.srcAddr;
			lib_semPost(s_semTx);
		}else if(s_optMode == 2){
			memcpy(s_rxBuffer, pkt->payload, payloadLen);
			s_rxLength = payloadLen;
			lib_semPost(s_semRx);
		}
	}
	return 0;
}
void tx_thread(void* obj, int* terminate){
	void* mrf = obj;
	int ret;
	LREP("tx thread is running.\n");
	while((*terminate) == 0){
		ret = lib_semPend(s_semTx, 100);
		if(ret < 0){
			LREP_WARN("pend sem failed.\n");
			break;
		}else if(ret > 0){
			//LREP(".");

//			lib_sleepMs(10);
			//DUMP( s_txBuffer, s_txLength, "tx --> %d", s_txDestId);
			mrf24j40_sendDataPacket16(mrf, s_txBuffer, s_txLength,
								0xcafe, s_txDestId, 1, 0, 0, 0);
		}
	}
	LREP("tx thread is stopped.\n");
}
