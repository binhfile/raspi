/*
 * File:   main.c
 * Author: dev
 *
 * Created on October 19, 2015, 11:19 AM
 */

#include <includes.h>
#include "xc.h"
#include "prj_cfg.h"
#include <lib_debug.h>

void App_Error(){
    while(1){
        LATEbits.LATE6   = 1;
        App_Delay(500);
        LATEbits.LATE6   = 0;
        App_Delay(500);     
    }
}
OS_STK  AppStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK  AppStartTaskStk2[APP_TASK_START_STK_SIZE];
static  void  AppStartTask (void *p_arg);
static  void  AppStartTask2 (void *p_arg);
int main(void) {   
    int cnt = 0;
    TRISEbits.TRISE6 = 0;
    LATEbits.LATE6   = 1;
    
    App_Initialize();
    LREP("Initialize done\r\n");
    
    TRISEbits.TRISE5 = 0;
    LATEbits.LATE5   = 1;
    
    OSInit(); 
    OSTaskCreateExt(AppStartTask,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk[0],
                    APP_TASK_START_PRIO,
                    APP_TASK_START_PRIO,
                    (OS_STK *)&AppStartTaskStk[APP_TASK_START_STK_SIZE-1],
                    APP_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSTaskCreateExt(AppStartTask2,
                    (void *)0,
                    (OS_STK *)&AppStartTaskStk2[0],
                    APP_TASK_START_PRIO+2,
                    APP_TASK_START_PRIO+2,
                    (OS_STK *)&AppStartTaskStk2[APP_TASK_START_STK_SIZE-1],
                    APP_TASK_START_STK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSStart();/* Start multitasking (i.e. give control to uC/OS-II)       */
    return 0;
}
static  void  AppStartTask (void *p_arg)
{
    int cnt = 0;
    while(1){
//        LREP("LED off %d\r\n", cnt);
        LATEbits.LATE5   = 1;
//        OSTimeDlyHMSM(0, 0, 0, 10);
//        App_Delay(500);
//        LREP("LED on\r\n");
        LATEbits.LATE5   = 0;
//        App_Delay(500);  
//        OSTimeDlyHMSM(0, 0, 0, 10);
        cnt++;
    }
}
static  void  AppStartTask2 (void *p_arg)
{
    int cnt = 0;
    while(1){
        LREP("LED2 off %d\r\n", cnt);
        OSTimeDlyHMSM(0, 0, 0, 25);
//        App_Delay(500);
        LREP("LED2 on\r\n");
        LATEbits.LATE6   = 0;
//        OSTimeDlyHMSM(0, 0, 0, 25); 
        cnt++;
    }
}
//end of file


