/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                              (c) Copyright 1992-2009, Micrium, Weston, FL
*                                           All Rights Reserved
*
* File    : uCOS_II.C
* By      : Jean J. Labrosse
* Version : V2.91
*
* LICENSING TERMS:
* ---------------
*   uC/OS-II is provided in source form for FREE evaluation, for educational use or for peaceful research.  
* If you plan on using  uC/OS-II  in a commercial product you need to contact Micriµm to properly license 
* its use in your product. We provide ALL the source code for your convenience and to help you experience 
* uC/OS-II.   The fact that the  source is provided does  NOT  mean that you can use it without  paying a 
* licensing fee.
*********************************************************************************************************
*/

#define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
#include <ucos_ii.h>


#define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
//#include <os_core.c>
//#include <os_flag.c>
//#include <os_mbox.c>
//#include <os_mem.c>
//#include <os_mutex.c>
//#include <os_q.c>
//#include <os_sem.c>
//#include <os_task.c>
//#include <os_time.c>
//#include <os_tmr.c>

INT8U             OSCPUUsage;
INT32U            OSIdleCtrMax;             /* Max. value that idle ctr can take in 1 sec.     */
INT32U            OSIdleCtrRun;             /* Val. reached by idle ctr at run time in 1 sec.  */
BOOLEAN           OSStatRdy;                /* Flag indicating that the statistic task is rdy  */
OS_STK            OSTaskStatStk[OS_TASK_STAT_STK_SIZE];      /* Statistics task stack          */
INT8U             OSIntNesting;             /* Interrupt nesting level                         */

INT8U             OSLockNesting;            /* Multitasking lock nesting level                 */

INT8U             OSPrioCur;                /* Priority of current task                        */
INT8U             OSPrioHighRdy;            /* Priority of highest priority task               */

OS_PRIO           OSRdyGrp;                        /* Ready list group                         */
OS_PRIO           OSRdyTbl[OS_RDY_TBL_SIZE];       /* Table of tasks which are ready to run    */

BOOLEAN           OSRunning;                       /* Flag indicating that kernel is running   */

INT8U             OSTaskCtr;                       /* Number of tasks created                  */

volatile  INT32U  OSIdleCtr;                                 /* Idle counter                   */
OS_STK            OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE];      /* Idle task stack                */


OS_TCB           *OSTCBCur;                        /* Pointer to currently running TCB         */
OS_TCB           *OSTCBFreeList;                   /* Pointer to list of free TCBs             */
OS_TCB           *OSTCBHighRdy;                    /* Pointer to highest priority TCB R-to-R   */
OS_TCB           *OSTCBList;                       /* Pointer to doubly linked list of TCBs    */
OS_TCB           *OSTCBPrioTbl[OS_LOWEST_PRIO + 1u];    /* Table of pointers to created TCBs   */
OS_TCB            OSTCBTbl[OS_MAX_TASKS + OS_N_SYS_TASKS];   /* Table of TCBs                  */
#if OS_TIME_GET_SET_EN > 0u
volatile  INT32U  OSTime;                   /* Current value of system time (in ticks)         */
#endif
INT32U            OSCtxSwCtr;

