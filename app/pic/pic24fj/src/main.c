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
	unsigned int reset;
	reset = RCON;
    BSP_Init();
    OSInit();

    App_Initialize();
    LREP("\r\nstartup %04X\r\n", reset);

    pthread_attr_setstackaddr(&sys_initialize_task_attr, Sys_Initialize_Stack);
    pthread_attr_setstacksize(&sys_initialize_task_attr, 512);
    pthread_setschedprio(sys_initialize_task, 0);
    pthread_create(&sys_initialize_task, &sys_initialize_task_attr, Sys_Initialize, 0);

    OSStart();
    return 0;
}
#define TEST_LEN 128
unsigned char tx[TEST_LEN], rx[TEST_LEN];
static  void  *Sys_Initialize (void *p_arg)
{
    struct DRV_GPIO_WRITE  gpio_write; 
    struct spi_ioc_transfer spi_xfer;
    unsigned char cnt = 0;
    int i, ret=-1;
    unsigned int address;
    
    pthread_attr_setstackaddr(&app_task_task_attr, App_Task_Stack);
    pthread_attr_setstacksize(&app_task_task_attr, 256);
    pthread_setschedprio(app_task_task, 2);
    pthread_create(&app_task_task, &app_task_task_attr, App_Task, 0);

    // test
	gpio_write.pin 		= RESET_PIN;
    gpio_write.value 	= 0;
    ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
    msleep(10);
    gpio_write.value 	= 1;
    ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);
    msleep(20);

    address = 0x04;
    cnt = 0xCC;
	tx[0] = ((address << 1) & 0b01111110) | 0x01;
	tx[1] = cnt;

	spi_xfer.bits_per_word = 8;
	spi_xfer.len = 2;
	spi_xfer.rx_buf = (unsigned int)&rx[0];
	spi_xfer.tx_buf = (unsigned int)&tx[0];
	spi_xfer.speed_hz = 1000000L;
	spi_xfer.timeout = OS_TICKS_PER_SEC;
	ret = ioctl(g_fd_spi_1, SPI_IOC_MESSAGE(1), &spi_xfer);
	LREP("xfer len = %d\r\n", ret);

	tx[0] = (address << 1 & 0b01111110);
	tx[1] = 0;
	rx[0] = 0;
	rx[1] = 0;
	ret = ioctl(g_fd_spi_1, SPI_IOC_MESSAGE(1), &spi_xfer);
	LREP("xfer len = %d %02X %02X\r\n", ret, rx[0], rx[1]);
	//
    gpio_write.value = 0;
    while(1){
        LREP(".");

    	for(i = 0; i < TEST_LEN; i++){
    		rx[i] = 0;
    	}
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


