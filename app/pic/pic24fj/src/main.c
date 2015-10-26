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
#include <drv/drv_api.h>
#include <drv/chip/pic24fj/drv_gpio.h>

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <lib_debug.h>

OS_STK  AppStartTaskStk[128];
OS_STK  AppStartTaskStk2[128];

pthread_t thread_1, thread_2;
pthread_attr_t attr_thread_1, attr_thread_2;
static  void  *AppStartTask (void *p_arg);
static  void  *AppStartTask2 (void *p_arg);
int main(void) {
    BSP_Init();
    OSInit();

    App_Initialize();
    LREP("Initialize done\r\n");

    pthread_attr_setstackaddr(&attr_thread_1, AppStartTaskStk);
    pthread_attr_setstacksize(&attr_thread_1, 128);
    pthread_setschedprio(thread_1, APP_TASK_START_PRIO);
    
    pthread_attr_setstackaddr(&attr_thread_2, AppStartTaskStk2);
    pthread_attr_setstacksize(&attr_thread_2, 128);
    pthread_setschedprio(thread_2, APP_TASK_START_PRIO+2);
    
    pthread_create(&thread_1, &attr_thread_1, AppStartTask, 0);
    pthread_create(&thread_2, &attr_thread_2, AppStartTask2, 0);

    OSStart();
    return 0;
}
static  void  *AppStartTask (void *p_arg)
{
    struct DRV_GPIO_WRITE  gpio_write; 
    
    gpio_write.pin = LED_STATUS;
    gpio_write.value = 0;

    while(1){
        LREP(".");
        gpio_write.value = !gpio_write.value;
        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
        msleep(500);
    }
    return 0;
}
static  void  *AppStartTask2 (void *p_arg)
{
	int ret;
	if(g_fd_ext_intr_1 <= 0){
		LREP("external interrupt setup failed, exit task\r\n");
		while(1){
			sleep(1);
		}
	}
    while(1){
    	ret = poll(g_fd_ext_intr_1, OS_TICKS_PER_SEC*5);
    	if(ret == OS_ERR_NONE) LREP("+");
    	else if(ret == OS_ERR_TIMEOUT) LREP("-");
    	else{
    		LREP("error %d", ret);
    		while(1){
    			sleep(1);
    		}
    	}
    	sleep(1);
    }
    return 0;
}
//end of file


