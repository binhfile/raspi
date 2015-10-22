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
#include <lib_debug.h>

OS_STK  AppStartTaskStk[APP_TASK_START_STK_SIZE];
OS_STK  AppStartTaskStk2[APP_TASK_START_STK_SIZE];
static  void  AppStartTask (void *p_arg);
static  void  AppStartTask2 (void *p_arg);
int main(void) {       
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
    struct DRV_GPIO_WRITE  gpio_write; 
    struct DRV_GPIO_READ   gpio_read;
    
    gpio_write.pin = DRV_GPIO_RE5;    
    gpio_read.pin  = DRV_GPIO_RE7;
    
    while(1){
        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_READ, &gpio_read);
        gpio_write.value = gpio_read.value;
        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
        OSTimeDlyHMSM(0, 0, 0, 100);
    }
}
static  void  AppStartTask2 (void *p_arg)
{
    struct DRV_GPIO_WRITE  gpio_write;    
    int cnt = 0;

    gpio_write.pin = DRV_GPIO_RE6;
    gpio_write.value = DRV_GPIO_LOW;
    ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
    while(1){
        gpio_write.value = DRV_GPIO_HIGH;
        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
        OSTimeDlyHMSM(0, 0, 0, 200);
        gpio_write.value = DRV_GPIO_LOW;
        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
        OSTimeDlyHMSM(0, 0, 0, 200);
        cnt++;
    }
}
//end of file


