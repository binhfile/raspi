/* 
 * File:   main.c
 * Author: dev
 *
 * Created on October 8, 2015, 9:28 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ucos_ii.h>

void UserTask (void *pdata)
{
    pdata = pdata;
    /* User task initialization */
    while (1) {
        /* User code goes here */
        /* You MUST invoke a service provided by µC/OS-II to: */
        /* ... a) Delay the task for ?n? ticks */
        /* ... b) Wait on a semaphore */
        /* ... c) Wait for a message from a task or an ISR */
        /* ... d) Suspend execution of this task */
    }
}
OS_STK taskStack[512];
void main(void) {
    /* Perform PIC Initializations */
    OSInit();
    /* Create at least one task by calling OSTaskCreate() */
    OSTaskCreate (UserTask,
                    0,
                    &taskStack[0],
                    5);
    OSStart();
    return;
}
void          OSTaskReturnHook        (OS_TCB          *ptcb){
    
}

