/*
 * frw_gpio_sysfs.c
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */
#include "frw_gpio_internal.h"

extern void HWL_GPIO_PIN_AS_DIGITAL(unsigned char pin);
extern void HWL_GPIO_PIN_DIRECTORY(unsigned char pin, unsigned char dir);
extern void HWL_GPIO_PIN_WRITE(unsigned char pin, unsigned char val);
extern unsigned char HWL_GPIO_PIN_READ(unsigned char pin);
extern char HWL_GPIO_PULLUP(unsigned char pin, unsigned char set);

int frw_gpioGetDeviceSize(){
    return sizeof(FRW_GPIO_DEVICE_INTERNAL);
}
int frw_gpioInit(void* frw_dev, int pinNum){
    FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
    int ret = -1;
    if(dev){
        dev->pinNum = pinNum;
        HWL_GPIO_PIN_AS_DIGITAL(dev->pinNum);
        ret = 0;
    }
    return ret;
}
int frw_gpioDestroy(void* frw_dev){
    FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
    int ret = -1;
    if(dev){
        ret = 0;
    }
    return ret;
}
int frw_gpioSetDirectory(void* frw_dev, int dir){
    FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
    int ret = -1;
    if(dev){
        HWL_GPIO_PIN_DIRECTORY(dev->pinNum, dir);
        ret = 0;
    }
    return ret;
}
int frw_gpioSetInterrupt(void* frw_dev, int intr){
    FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
    int ret = -1;
    if(dev){

    }
    return ret;
}
int frw_gpioWrite(void* frw_dev, int value){
    HWL_GPIO_PIN_WRITE(((FRW_GPIO_DEVICE_INTERNAL*)frw_dev)->pinNum, value);
    return 0;
}
int frw_gpioRead(void* frw_dev){
    return HWL_GPIO_PIN_READ(((FRW_GPIO_DEVICE_INTERNAL*)frw_dev)->pinNum);
}
int frw_gpioWaitEvent(void* frw_dev, int timeout){
    FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
    int ret = -1;
    if(dev){
    
    }
    return ret;
}
int frw_gpioSetPull(void* frw_dev, int pull){
    if(pull == 0){
        HWL_GPIO_PULLUP(((FRW_GPIO_DEVICE_INTERNAL*)frw_dev)->pinNum, 0);
    }else if(pull == 1){
        HWL_GPIO_PULLUP(((FRW_GPIO_DEVICE_INTERNAL*)frw_dev)->pinNum, 1);
    }else{
        HWL_GPIO_PULLUP(((FRW_GPIO_DEVICE_INTERNAL*)frw_dev)->pinNum, 0);
    }
    return 0;
}


