/*
 * File:   main.c
 * Author: dev
 *
 * Created on October 19, 2015, 11:19 AM
 */


#include "xc.h"
#include "app_cfg.h"
#include <drv/drv_api.h>
#include <drv/chip/pic24fj/drv_usart.h>

#include <frw_string.h>

int main(void) {
    int fdUart;
    char buffer[128];
    struct termios2 opt;
    int ret;
    
    App_Initialize();
    strcpy(buffer, "hello\r\n");
    fdUart = open("usart0", 0);
    
    ret = ioctl(fdUart, TCGETS2, (unsigned int)&opt);
    opt.c_ispeed = 115200;
    opt.c_ospeed = 115200;
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_cflag &= ~CSTOPB;
    opt.c_cflag &= ~PARENB;
    opt.c_iflag &= ~INPCK;
    ret = ioctl(fdUart, TCSETS2, (unsigned int)&opt);
    
    ret = read(fdUart, buffer, 128);
    while(1){
        ret = write(fdUart, buffer, 128);
    }
    close(fdUart);
    return 0;
}
