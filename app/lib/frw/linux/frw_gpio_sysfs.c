/*
 * frw_gpio_sysfs.c
 *
 *  Created on: Oct 6, 2015
 *      Author: dev
 */
#include "frw_gpio_sysfs_internal.h"
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <poll.h>
int frw_gpioGetDeviceSize(){
	return sizeof(FRW_GPIO_DEVICE_INTERNAL);
}
int frw_gpioInit(void* frw_dev, int pinNum){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1, fd;
	char szBuffer[512];
	if(dev){
		dev->pinNum = pinNum;
		dev->handle = -1;
		snprintf(szBuffer, 511, "%d", dev->pinNum);
		fd = open("/sys/class/gpio/export", O_WRONLY);
		if(fd >= 0){
			write(fd, szBuffer, strlen(szBuffer));
			close(fd);
			snprintf(szBuffer, 511, "/sys/class/gpio/gpio%d/value", dev->pinNum);
			fd = open(szBuffer, O_RDWR);
			if(fd >= 0){
				dev->handle = fd;
				ret = 0;
			}
		}
	}
	return ret;
}
int frw_gpioDestroy(void* frw_dev){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1, fd;
	char szBuffer[512];
	if(dev && dev->handle != -1){
		close(dev->handle);
		dev->handle = -1;
		snprintf(szBuffer, 511, "%d", dev->pinNum);
		fd = open("/sys/class/gpio/unexport", O_WRONLY);
		if(fd >= 0){
			write(fd, szBuffer, strlen(szBuffer));
			close(fd);
			ret = 0;
		}
	}
	return ret;
}
int frw_gpioSetDirectory(void* frw_dev, int dir){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1, fd;
	char szBuffer[512];
	if(dev && dev->handle != -1){
		snprintf(szBuffer, 511, "/sys/class/gpio/gpio%d/direction", dev->pinNum);
		fd = open(szBuffer, O_WRONLY);
		if(fd >= 0){
			strncpy(szBuffer, "in", 511);
			if(dir == 1) strncpy(szBuffer, "in", 511);
			else if(dir == 0) strncpy(szBuffer, "out", 511);
			write(fd, szBuffer, strlen(szBuffer));
			close(fd);
			ret = 0;
		}
	}
	return ret;
}
int frw_gpioSetInterrupt(void* frw_dev, int intr){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1, fd;
	char szBuffer[512];
	if(dev && dev->handle != -1){
		frw_gpioSetDirectory(dev, 1);
		snprintf(szBuffer, 511, "/sys/class/gpio/gpio%d/edge", dev->pinNum);
		fd = open(szBuffer, O_WRONLY);
		if(fd >= 0){
			strncpy(szBuffer, "none", 511);
			if(intr == 0) strncpy(szBuffer, "none", 511);
			else if(intr == 1) strncpy(szBuffer, "falling", 511);
			else if(intr == 2) strncpy(szBuffer, "rising", 511);
			else if(intr == 3) strncpy(szBuffer, "both", 511);
			write(fd, szBuffer, strlen(szBuffer));
			close(fd);
			ret = 0;
		}
	}
	return ret;
}
int frw_gpioWrite(void* frw_dev, int value){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1;
	char szBuffer[512];
	if(dev && dev->handle != -1){
		write(dev->handle, ((value == 0) ? "0" : "1"), 1);
		ret = 0;
	}
	return ret;
}
int frw_gpioRead(void* frw_dev){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1;
	char szBuffer[512];
	if(dev && dev->handle != -1){
		szBuffer[0] = 0;
		read(dev->handle, szBuffer, 1);
		if(szBuffer[0] == '0')
			ret = 0;
		else
			ret = 1;
	}
	return ret;
}
int frw_gpioWaitEvent(void* frw_dev, int timeout){
	FRW_GPIO_DEVICE_INTERNAL* dev = (FRW_GPIO_DEVICE_INTERNAL*)frw_dev;
	int ret = -1;
	char szBuffer[512];
	struct pollfd fdset[1];
	int nfds = 1;
	int rc;
	if(dev && dev->handle != -1){
		if(timeout < 0) timeout = 0;
		memset((void*)fdset, 0, sizeof(fdset));
		fdset[0].fd 	= dev->handle;
		fdset[0].events = POLLPRI;
		rc = poll(fdset, nfds, timeout);
		if(rc < 0) ret = -2;
		else if(rc == 0) ret = 0;
		else{
			if (fdset[0].revents & POLLPRI) {
				lseek(dev->handle, 0, SEEK_SET);
				szBuffer[0] = 0;
				rc = read(dev->handle, szBuffer, 512);
				if(rc > 0 && rc <= 512){
					if(szBuffer[rc-1] == 0)
						ret = 1;
					else ret = 2;
				}else ret = -4;
			}
			else ret = -3;
		}
	}
	return ret;
}



