#include <lib_debug.h>
#include <lib_time.h>
#include <mrf24j40/mrf24j40.h>

#include <stdio.h>
#include <string.h>

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

int main(int argc, char** argv){
	void		*txThread = 0;
	const char 	*portName 	= argv[1];
	int 		resetPin 	= atoi(argv[2]);
	int 		intrPin 	= atoi(argv[3]);
	unsigned short id  		= atoi(argv[4]);
	unsigned short channel  = atoi(argv[5]);
	char 		szInput[32];
	int j, i;
	unsigned short destid;
	unsigned char cnt = 0;
	int ret;
	int failedCnt = 0;
	int passedCnt = 0;
	int totalBytes = 0;
	unsigned int timeNow, timeEnd;
	int retries = 0;
	int passed;
	unsigned int timeDiff;
	float speed;
	unsigned char *tx, *rx;;

	if(argc < 6){
		LREP("usage: %s /dev/spidevX.Y resetPin intrPin id channel\n", argv[0]);
		return 0;
	}

	LREP("cmd='%s'\nreset=%d\nintr=%d id=0x%04X channel=%d\n", portName, resetPin, intrPin, id, channel);

	s_semTx = lib_semAlloc(0);
	s_semRx = lib_semAlloc(0);
	txThread = lib_threadAlloc(tx_thread);

	void* mrf = mrf24j40_allocDevice(
			portName,
			resetPin,
			intrPin);
	if(mrf24j40_openDevice(mrf) != 0){
		LREP("open device failed.\n");
		mrf24j40_freeDevice(mrf);
		return 0;
	}
	LREP("open done\n");
	mrf24j40_setCallback(mrf, mac_callback, mrf);
	mrf24j40_setPan(mrf, 0xcafe);
	mrf24j40_setAddress16(mrf, id);
	mrf24j40_setAddress32(mrf, id);
	mrf24j40_setChannel(mrf, channel);
	mrf24j40_setTurboMode(mrf, 1);
	mrf24j40_initDevice(mrf);

	lib_threadStart(txThread, mrf);

	while(1){
		LREP(">");
		scanf("%s", szInput);
		if(strcmp(szInput, "q") == 0) break;
		else if(strcmp(szInput, "s") == 0){
			LREP("id  >");
			scanf("%s", szInput);
			destid = atoi(szInput);
			LREP("send>");
			scanf("%s", szInput);
			tx = mrf24j40_getTxPayload(mrf);
			memcpy(tx, szInput, strlen(szInput));
			mrf24j40_sendDataPacket16(mrf, strlen(szInput),
					0xcafe, destid, 1, 0, 0, 0);
		}
		else if(strcmp(szInput,"i") == 0){
			mrf24j40_initDevice(mrf);
		}
		else if(strcmp(szInput, "r")==0){
			LREP("goto rx mode.\n");
			s_optMode = 1;
		}
		else if(strcmp(szInput, "t")==0){
			LREP("goto tx mode.\n");
			LREP("dest id>");
			scanf("%s", szInput);
			destid = atoi(szInput);
			LREP("payload len>");
			scanf("%s", szInput);
			int payloadLen = atoi(szInput);
			if(payloadLen > MAC_DATA_PAYLOAD_SIZE) payloadLen = MAC_DATA_PAYLOAD_SIZE;
			LREP("packet count>");
			scanf("%s", szInput);
			int pktCount = atoi(szInput);
			LREP("tx to %d payload len = %d packet count = %d\n", destid, payloadLen, pktCount);
			cnt = 0;
			s_optMode = 2;
			failedCnt = 0;
			passedCnt = 0;
			totalBytes = 0;
			timeNow = lib_timeGetCurrentMs();
			retries = 0;
			for(i = 0; i < pktCount; i++){
				tx = mrf24j40_getTxPayload(mrf);
				for(j = 0; j < payloadLen; j++){
					tx[j] = cnt++;
				}
				//LREP("send pkt %d ...", i + 1);
				mrf24j40_sendDataPacket16(mrf, payloadLen,
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
					passed = 1;
					if(s_rxLength != payloadLen) passed = 0;
					for(j = 0; j < payloadLen; j++){
						if(s_rxBuffer[j] != tx[j]){
							passed = 0;
							break;
						}
					}
					if(!passed){
						LREP("not match.\n");
//						DUMP(tx, payloadLen, "tx %d bytes", payloadLen);
//						DUMP(s_rxBuffer, s_rxLength, "rx %d bytes", s_rxLength);
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
			timeEnd = lib_timeGetCurrentMs();
			timeDiff = timeEnd - timeNow;
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
//		DUMP(pkt->payload, payloadLen, "%d --> rx %d bytes",pkt->header.srcAddr, payloadLen);

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
	void *tx;
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
			tx = mrf24j40_getTxPayload(mrf);
			memcpy(tx, s_txBuffer, s_txLength);
			mrf24j40_sendDataPacket16(mrf, s_txLength,
								0xcafe, s_txDestId, 1, 0, 0, 0);
		}
	}
	LREP("tx thread is stopped.\n");
}
