#include "../include/semaphore.h"
int sem_init (sem_t *__sem, int __pshared, unsigned int __value){
    __sem->event = OSSemCreate(__value);
    if(__sem->event != 0) return 0;
    return -1;
}
int sem_destroy (sem_t *__sem){
    return 0;
}
//int sem_wait (sem_t *__sem){
//    INT8U err = 0;
//    OSSemPend(__sem->event, 0, &err);
//    if(err == OS_ERR_NONE) return 0;
//    return -1;
//}
int sem_timedwait (sem_t * __sem, const struct timespec * __abstime){
    INT8U err = 0;
    OSSemPend(__sem->event, __abstime->tv_sec, &err);
    if(err == OS_ERR_NONE) return 0;
    return -1;
}
// end of file
