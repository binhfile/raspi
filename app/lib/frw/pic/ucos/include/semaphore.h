/* 
 * File:   semaphore.h
 * Author: dev
 *
 * Created on October 26, 2015, 10:18 AM
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <ucos_ii.h>
/* Value returned if `sem_open' failed.  */
#define SEM_FAILED      ((sem_t *) 0)

typedef union
{
    OS_EVENT *event;
} sem_t;
struct timespec
{
  unsigned int          tv_sec;		/* Seconds.  */
  unsigned long long    tv_nsec;     /* Nanoseconds.  */
};

/* Initialize semaphore object SEM to VALUE.  If PSHARED then share it
   with other processes.  */
int sem_init (sem_t *__sem, int __pshared, unsigned int __value);
/* Free resources associated with semaphore object SEM.  */
int sem_destroy (sem_t *__sem);
/* Wait for SEM being posted.

   This function is a cancellation point and therefore not marked with
   __THROW.  */
#define sem_wait(__sem) OSSemPend(((sem_t*)(__sem))->event, 0, 0)

/* Similar to `sem_wait' but wait only until ABSTIME.

   This function is a cancellation point and therefore not marked with
   __THROW.  
 note: __abstime.tv_sec is system tick count
 */
int sem_timedwait (sem_t * __sem,
			  const struct timespec * __abstime);

/* Post SEM.  */
#define sem_post(__sem) OSSemPost(((sem_t*)(__sem))->event)


#ifdef	__cplusplus
}
#endif

#endif	/* SEMAPHORE_H */

