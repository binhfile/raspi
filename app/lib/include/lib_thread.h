/*
 * lib_thread.h
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */

#ifndef LIB_INCLUDE_LIB_THREAD_H_
#define LIB_INCLUDE_LIB_THREAD_H_
#ifdef __cplusplus
extern "C" {
#endif
typedef void (*LIB_THREAD_ROUTINE)(void* obj, int *terminate);
typedef struct{
	LIB_THREAD_ROUTINE 	fxn;
	void*				obj;
	unsigned char		frw[1];
}LIB_THREAD;

void* lib_threadAlloc(LIB_THREAD_ROUTINE fxn);
int lib_threadFree(void* thread);
int lib_threadStart(void* thread, void* obj);
int lib_threadStop(void* thread, int timeout);

void  lib_sleepMs(int ms);
void  lib_sleepUs(int us);

#ifdef __cplusplus
}
#endif
#endif /* LIB_INCLUDE_LIB_THREAD_H_ */
