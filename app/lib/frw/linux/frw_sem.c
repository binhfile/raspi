/*
 * frw_sem.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#include "frw_sem_internal.h"
#include <time.h>
#include <errno.h>
#include <unistd.h>

int frw_semGetSize(){
	return sizeof(FRW_SEM);
}
int frm_semInit(void* frw_sem, int value){
	FRW_SEM* sem = (FRW_SEM*)frw_sem;
	int ret = -1;
	if(sem){
		sem_init(&sem->sem, 0, value);
		ret = 0;
	}
	return ret;
}
int frm_semDestroy(void* frw_sem){
	FRW_SEM* sem = (FRW_SEM*)frw_sem;
	int ret = -1;
	if(sem){
		sem_destroy(&sem->sem);
		ret = 0;
	}
	return ret;
}
int frw_semPend(void* frw_sem, int timeout){
	FRW_SEM* sem = (FRW_SEM*)frw_sem;
	int ret = -1;
	struct timespec ts;
	int s;

	if(sem){
		if(timeout == 0){
			sem_wait(&sem->sem);
			ret = 0;
		}else{
			if(clock_gettime(CLOCK_REALTIME, &ts) == 0)
			{
				ts.tv_sec += timeout / 1000;
				ts.tv_nsec+= (timeout % 1000) * 1000000;
				if(ts.tv_nsec > 1000000000)
				{
					ts.tv_sec += 1;
					ts.tv_nsec -= 1000000000;
				}

				while ((s = sem_timedwait(&sem->sem, &ts)) == -1 && errno == EINTR)
					continue;       /* Restart if interrupted by handler */
				if(s == 0){
					ret = 1;
				}
				else
				{
					if(errno == ETIMEDOUT)
						ret = 0;
					else{
						ret = -2;
					}
				}
			}
		}
	}
	return ret;
}
int frw_semPost(void* frw_sem){
	FRW_SEM* sem = (FRW_SEM*)frw_sem;
	int ret = -1;
	if(sem){
		sem_post(&sem->sem);
		ret = 0;
	}
	return ret;
}

