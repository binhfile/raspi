#include <xc.h>
#include "prj_cfg.h"
#include <drv/drv_api.h>
#include <drv/chip/pic24fj/drv_uart.h>

int g_fd_uart0 = -1;

void App_Initialize(){
    struct termios2 opt;
    UINT32 u32Val;
    
    drv_uartInitialize();
    
    g_fd_uart0 = open("uart0", 0);
    u32Val = FREQ_OSC * FREQ_PLL / FREQ_DIV / 2;
    ioctl(g_fd_uart0, UART_IOCTL_SET_FCY, (unsigned int)&u32Val);
    ioctl(g_fd_uart0, TCGETS2, (unsigned int)&opt);
    opt.c_ispeed = 9600;
    opt.c_ospeed = 9600;
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_cflag &= ~CSTOPB;
    opt.c_cflag &= ~PARENB;
    opt.c_iflag &= ~INPCK;
    ioctl(g_fd_uart0, TCSETS2, (unsigned int)&opt);
    
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
