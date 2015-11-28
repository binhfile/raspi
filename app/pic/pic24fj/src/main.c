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
#include <drv/chip/pic24fj/drv_spi.h>
#include <en25f80/en25f80.h>

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <lib_debug.h>

OS_STK  		Sys_Initialize_Stack[512];
pthread_t 		sys_initialize_task;
pthread_attr_t 	sys_initialize_task_attr;

OS_STK  		App_Task_Stack[512];
pthread_t 		app_task_task;
pthread_attr_t 	app_task_task_attr;

static  void  *Sys_Initialize (void *p_arg);
static  void  *App_Task (void *p_arg);
int main(void) {
    BSP_Init();
    OSInit();

    pthread_attr_setstackaddr(&sys_initialize_task_attr, Sys_Initialize_Stack);
    pthread_attr_setstacksize(&sys_initialize_task_attr, 512);
    pthread_setschedprio(sys_initialize_task, 0);
    pthread_create(&sys_initialize_task, &sys_initialize_task_attr, Sys_Initialize, 0);

    OSStart();
    return 0;
}
static  void  *Sys_Initialize (void *p_arg)
{
    struct DRV_GPIO_WRITE  gpio_write;
    int ret;
    struct DRV_EN25F80_ID flash_id;
    
    App_Initialize();
    LREP("\r\nstartup %04X\r\n", RCON);

//    pthread_attr_setstackaddr(&app_task_task_attr, App_Task_Stack);
//    pthread_attr_setstacksize(&app_task_task_attr, 256);
//    pthread_setschedprio(app_task_task, 2);
//    pthread_create(&app_task_task, &app_task_task_attr, App_Task, 0);

    // test
//    ret = ioctl(g_fd_flash, EN25F80_IOC_RD_ID, &flash_id);
//    if(ret >= 0){
//    	LREP("ID %02X %02X%02X\r\n",
//    			flash_id.manufacturer, flash_id.memory_type, flash_id.memory_capacity);
//    }else{
//    	LREP("get ID from flash failed\r\n");
//    }
	//
    gpio_write.value = DRV_GPIO_HIGH;
    while(1){
        LREP(".");
    	gpio_write.pin = LED_STATUS;
        gpio_write.value = !gpio_write.value;
        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
        msleep(500);
    }
    return 0;
}
static  void  *App_Task (void *p_arg)
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


