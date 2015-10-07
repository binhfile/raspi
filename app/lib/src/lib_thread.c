/*
 * lib_thread.c
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */
#include <lib_thread.h>
#include <lib_mem.h>
extern int frw_threadGetContextSize();
extern int frw_threadStart(void* frw, void* fxn, void* obj);
extern int frw_threadStop(void* frw, int timeout);
extern void frw_sleepMs();
extern void frw_sleepUs();

void  lib_sleepMs(int ms){
	frw_sleepMs(ms);
}
void  lib_sleepUs(int us){
	frw_sleepUs(us);
}
void* lib_threadAlloc(LIB_THREAD_ROUTINE fxn){
	int size = sizeof(LIB_THREAD) - 1 + frw_threadGetContextSize();
	LIB_THREAD* th = (LIB_THREAD*)lib_alloc(size);
	if(th){
		th->fxn = fxn;
		th->obj = 0;
	}
	return th;
}
int lib_threadFree(void* thread){
	LIB_THREAD* th = (LIB_THREAD*)thread;
	int ret = -1;
	if(th){
		lib_threadStop(th, 100);
		lib_free(th);
		ret = 0;
	}
	return ret;
}
int lib_threadStart(void* thread, void* obj){
	LIB_THREAD* th = (LIB_THREAD*)thread;
	int ret = -1;
	if(th){
		th->obj = obj;
		ret = frw_threadStart(th->frw, th->fxn, th->obj);
	}
	return ret;
}
int lib_threadStop(void* thread, int timeout){
	LIB_THREAD* th = (LIB_THREAD*)thread;
	int ret = -1;
	if(th){
		ret = frw_threadStop(th->frw, timeout);
	}
	return ret;
}



