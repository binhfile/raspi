#include "../include/pthread.h"
#include <ucos_ii.h>

int pthread_create (pthread_t * __newthread,
              const pthread_attr_t * __attr,
              void *(*__start_routine) (void *),
              void *__restrict __arg){
    int ret = -1;
    
    __newthread->attr = (pthread_attr_t*)__attr;
    __newthread->arg  = __arg;
    __newthread->start_routine = __start_routine;
    
    if(OSTaskCreate(
            (void (*)(void *))__newthread->start_routine,
            __newthread->arg, 
            __newthread->attr->ptos,
            __newthread->prio
            ) == OS_ERR_NONE)
        ret = 0;
    return ret;
}
 int pthread_attr_getstackaddr (const pthread_attr_t *
				      __attr, void ** __stackaddr){
     *__stackaddr = __attr->ptos;
     return 0;
 }

 int pthread_attr_setstackaddr (pthread_attr_t *__attr,
				      void *__stackaddr){
     __attr->ptos = __stackaddr;
     return 0;
 }
  int pthread_attr_getstacksize (const pthread_attr_t *
				      __attr, size_t * __stacksize){
      *__stacksize = __attr->ptos_size;
      return 0;
  }
  
 int pthread_attr_setstacksize (pthread_attr_t *__attr,
				      size_t __stacksize){
     __attr->ptos_size = __stacksize;
     return 0;
 }

 int pthread_setschedprio_ucos (pthread_t* __target_thread, int __prio){
     __target_thread->prio = __prio;
     return 0;
 }
// end of file
