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
sem_t sem_thread;
static  void  *AppStartTask (void *p_arg);
static  void  *AppStartTask2 (void *p_arg);
int main(void) {       
    App_Initialize();
    LREP("Initialize done\r\n");
    
    BSP_Init();
    OSInit();
    
    sem_init(&sem_thread, 0, 0);
    
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
    struct DRV_GPIO_READ   gpio_read;
    
    gpio_write.pin = DRV_GPIO_RE5;    
    gpio_read.pin  = DRV_GPIO_RE7;
    
    while(1){
        LREP(".");
//        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_READ, &gpio_read);
//        gpio_write.value = gpio_read.value;
//        ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
        sem_wait(&sem_thread);
    }
    return 0;
}
static  void  *AppStartTask2 (void *p_arg)
{
    struct DRV_GPIO_WRITE  gpio_write;    
//    int cnt = 0;

    gpio_write.pin = DRV_GPIO_RE6;
    gpio_write.value = DRV_GPIO_LOW;
    ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
    while(1){
        sleep(1);
        sem_post(&sem_thread);
    }
    return 0;
}
//end of file


