/*
 * lib_sem.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <lib_sem.h>
#include <lib_mem.h>
extern int frw_semGetSize();
extern int frm_semInit(void* frw_sem, int value);
extern int frm_semDestroy(void* frw_sem);

void* lib_semAlloc(int value){
	int size = sizeof(SEM_INTERNAL) - 1 + frw_semGetSize();
	SEM_INTERNAL* sem = (SEM_INTERNAL*)lib_alloc(size);
	if(sem){
		frm_semInit(sem->frw_sem, value);
	}
	return sem;
}
int   lib_semFree(void* sem){
	SEM_INTERNAL* _sem = (SEM_INTERNAL*)sem;
	int ret = -1;
	if(_sem){
		ret = frm_semDestroy(_sem->frw_sem);
	}
	return ret;
}



