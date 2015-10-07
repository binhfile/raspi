/*
 * frw_thread.c
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */

#include "frw_thread_internal.h"
#include <unistd.h>

void frw_sleepMs(int ms){
	usleep(1000 * ms);
}
void frw_sleepUs(int us){
	usleep(1000 * us);
}
void* frw_threadRoutine(void* obj){
	FRW_THREAD_INTERNAL* th = (FRW_THREAD_INTERNAL*)obj;
	FRW_THREAD_ROUTINE fxn = (FRW_THREAD_ROUTINE)th->fxn;
	fxn(th->obj, &th->terminate);
	return 0;
}

int frw_threadGetContextSize(){
	return sizeof(FRW_THREAD_INTERNAL);
}
int frw_threadStart(void* frw, void* fxn, void* obj){
	FRW_THREAD_INTERNAL* th = (FRW_THREAD_INTERNAL*)frw;
	int ret = -1;
	if(th){
		th->terminate = 0;
		th->fxn = fxn;
		th->obj = obj;
		pthread_create(&th->handle, 0, frw_threadRoutine, th);
		ret = 0;
	}
	return ret;
}
int frw_threadStop(void* frw, int timeout){
	FRW_THREAD_INTERNAL* th = (FRW_THREAD_INTERNAL*)frw;
	int ret = -1;
	if(th){
		th->terminate = 1;
		pthread_join(th->handle, 0);
		ret = 0;
	}
	return ret;
}

