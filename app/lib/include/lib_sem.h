/*
 * lib_sem.h
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#ifndef LIB_INCLUDE_LIB_SEM_H_
#define LIB_INCLUDE_LIB_SEM_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "internal/lib_sem_internal.h"

extern int frw_semPend(void* frw_sem, int timeout);
extern int frw_semPost(void* frw_sem);

void* lib_semAlloc(int value);
int   lib_semFree(void* sem);
#define lib_semPend(sem, timeout)		frw_semPend(((SEM_INTERNAL*)sem)->frw_sem, timeout)
#define lib_semPost(sem)				frw_semPost(((SEM_INTERNAL*)sem)->frw_sem)

#ifdef __cplusplus
}
#endif
#endif /* LIB_INCLUDE_LIB_SEM_H_ */
