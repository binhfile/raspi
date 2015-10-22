#include <xc.h>
#include "prj_cfg.h"
#include <drv/drv_api.h>
#include <drv/chip/pic24fj/drv_uart.h>
#include <drv/chip/pic24fj/drv_common.h>

int g_fd_uart0 = -1;
void App_Error(){
    while(1){
        LATEbits.LATE6 = 0;
    }
}
void App_Initialize(){
    struct termios2 opt;
    struct UART_MAP_PIN map_pin;
    struct COMMON_SET_OSC osc;
    int fd;

    drv_initialize();   // Load all driver is link
    // Common DRV
    osc.frc         = 8000000L;
    osc.primary     = 25000000L;
    osc.secondary   = 25000000L;
    osc.low_power   = 31000L;
    fd = drv_findFdByName("common");
    ioctl(fd, COMMON_IOCTL_SET_OSC_FREQ, (unsigned int)&osc);
    // UART DRV
    g_fd_uart0 = open("uart0", 0);
    if(g_fd_uart0 < 0) App_Error();
    ioctl(g_fd_uart0, TCGETS2, (unsigned int)&opt);
    opt.c_ispeed = 9600;
    opt.c_ospeed = 9600;
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_cflag &= ~CSTOPB;
    opt.c_cflag &= ~PARENB;
    opt.c_iflag &= ~INPCK;
    ioctl(g_fd_uart0, TCSETS2, (unsigned int)&opt);
    map_pin.rx = 7;
    map_pin.tx = 6;
    ioctl(g_fd_uart0, UART_IOCTL_MAP_PIN, (unsigned int)&map_pin);
    
}
void frw_debugPrint(const void* sz){
    write(g_fd_uart0, sz, strlen(sz));
}
void __attribute__ ((interrupt, no_auto_psv)) _U1RXInterrupt(void){
    IFS0bits.U1RXIF = 0;
}
void __attribute__ ((interrupt, no_auto_psv)) _U1TXInterrupt(void){
    IFS0bits.U1TXIF = 0;
}
void __attribute__ ((interrupt, no_auto_psv)) _U1ErrInterrupt(void){
    IFS4bits.U1ERIF = 0;
}
//end of file
