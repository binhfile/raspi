/*
 * File:   main.c
 * Author: dev
 *
 * Created on October 19, 2015, 11:19 AM
 */
/*
  gen deassambly file : xc16-objdump -S test-pic24fj.X.production.elf > test.lst
 */

#include <includes.h>
#include "xc.h"
#include "prj_cfg.h"
#include <lib_debug.h>

OS_STK  AppStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK  AppStartTaskStk2[APP_TASK_START_STK_SIZE];
static  void  AppStartTask (void *p_arg);
static  void  AppStartTask2 (void *p_arg);
int main(void) {   
    TRISEbits.TRISE6 = 0;
    LATEbits.LATE6   = 1;
    TRISEbits.TRISE5 = 0;
    LATEbits.LATE5   = 1;
    
    App_Initialize();
    LREP("Initialize done\r\n");
    
    BSP_Init();
    OSInit();     
    OSTaskCreate(AppStartTask,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk[0],
                    APP_TASK_START_PRIO);
    OSTaskCreate(AppStartTask2,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk2[0],
                    APP_TASK_START_PRIO+2);
    OSStart();
    return 0;
}
static  void  AppStartTask (void *p_arg)
{
    int cnt = 0;
    while(1){
        LREP("LED off %d\r\n", cnt);
        LATEbits.LATE5   = 1;
        OSTimeDlyHMSM(0, 0, 1, 0);
        LREP("LED on\r\n");
        LATEbits.LATE5   = 0;
        OSTimeDlyHMSM(0, 0, 1, 0);
        cnt++;
    }
}
static  void  AppStartTask2 (void *p_arg)
{
    int cnt = 0;
    while(1){
        LATEbits.LATE6   = 1;
        OSTimeDlyHMSM(0, 0, 0, 200);
        LATEbits.LATE6   = 0;
        OSTimeDlyHMSM(0, 0, 0, 200);
        cnt++;
    }
}
//end of file


