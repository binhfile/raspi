/*
 * frw_thread_internal.h
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */

#ifndef LIB_FRW_LINUX_FRW_THREAD_INTERNAL_H_
#define LIB_FRW_LINUX_FRW_THREAD_INTERNAL_H_
#include <pthread.h>
typedef void (*FRW_THREAD_ROUTINE)(void* obj, int *terminate);
typedef struct{
	pthread_t handle;
	void* fxn;
	void* obj;
	int   terminate;
}FRW_THREAD_INTERNAL;




#endif /* LIB_FRW_LINUX_FRW_THREAD_INTERNAL_H_ */
