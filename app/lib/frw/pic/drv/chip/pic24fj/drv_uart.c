#include "drv_uart.h"
#include "drv_regs.h"
#include "../../drv_api.h"
#include <frw_string.h>
#include <p24FJ128GA106.h>

struct DRV_UART{
    int         index;
    UINT32      Fcy;
    DRV_ELEM    drv;
};
//const char          *g_uart_name[] = {"uart0"};
//struct DRV_UART     g_uart[1];

int drv_uart_open(void *drv, int flags){
    int ret = -1;
    struct DRV_UART* _drv;
    unsigned int base_reg;
    
    _drv = container_of(drv, struct DRV_UART, drv);
    if(_drv->index < 0 || _drv->index > UART_MODULE_COUNT)
        return ret;
    /* 1.Setup 
     *  data, parity, stop
     *  baud rate
     *  interrupt
     * 2. Enable
     * 3. Set UTXEN
     * 4. Write UxTXREG
     */
    base_reg = UART_REG_BASE_ADDR + (UART_REG_MODULE_LEN * _drv->index);
    REG(base_reg+UART_REG_MODE)= 0b1000000000001000;
                        /*         ||||||| |||||| |__ STSEL One stop bit
                         *         ||||||| ||||||____ PDSEL 8 bit, no parity
                         *         ||||||| |||||_____ BRGH  High speed mode rate
                         *         ||||||| ||||______ RXINV RX idle state is 1
                         *         ||||||| |||_______ ABAUD Baud rate measure disabled
                         *         ||||||| ||________ LPBACK UART loop back disabled
                         *         ||||||| |_________ WAKE  No wake-up enabled
                         *         |||||||___________ UEN   TX, RX enable, CTS, RTS/BCLK controlled by port latches
                         *         ||||||
                         *         |||||_____________ RTSMD  RTS in Flow Control mode
                         *         ||||______________ IREN   IrDA disabled
                         *         |||_______________ USIDL  Continue module operation in Idle mode
                         *         ||
                         *         |_________________ UARTEN UART enable
                         * 
                         */
    REG(base_reg +UART_REG_STA)= 0b1000010000000000;
                        /*         ||||||||| ||||||__ URXDA
                         *         ||||||||| |||||___ OERR  Receive buffer overrun error status
                         *         ||||||||| ||||____ FERR
                         *         ||||||||| |||_____ PERR
                         *         ||||||||| ||______ RIDLE
                         *         ||||||||| |_______ ADDEN     Address detect mode disabled
                         *         |||||||||_________ URXISEL   Interrupt is set when any character is received
                         *         ||||||||__________ TRMT      
                         *         |||||||___________ UTXBF
                         *         ||||||____________ UTXEN     Transmit enable
                         *         |||||_____________ UTXBRK    Sync break transmission disabled
                         *         |||_______________ UTXISEL0  0 
                         *         ||________________ UTXINV    TX Idle '1'
                         *         |_________________ UTXISEL0  1 Interrupt when a character is transfered to TSR
                         * 
                         */
    /* BRG = Fcy / 16 / Baudrate - 1, Fcy = FOSC / 2 (FRC)
     */
    REG(base_reg + UART_REG_BRG)  = 25;// Default 9600@8Mhz 
    // Map pin
    RPINR18bits.U1RXR   = 6;    // RP6
    RPOR3bits.RP7R      = 3;    // RP7
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
    IEC4bits.U1ERIE = 0;
    ret = 0;
    return ret;
}
int drv_uart_close(void *drv){
    int ret = -1;
    struct DRV_UART* _drv;
    unsigned int base_reg;
    
    _drv = container_of(drv, struct DRV_UART, drv);
    if(_drv->index < 0 || _drv->index > UART_MODULE_COUNT)
        return ret;
    base_reg = UART_REG_BASE_ADDR + (UART_REG_MODULE_LEN * _drv->index);
    IEC0bits.U1RXIE = 0;
    IEC0bits.U1TXIE = 0;
    IEC4bits.U1ERIE = 0;
    REG(base_reg+UART_REG_MODE)= 0b0000000000000000;
                        /*         ||||||| |||||| |__ STSEL One stop bit
                         *         ||||||| ||||||____ PDSEL 8 bit, no parity
                         *         ||||||| |||||_____ BRGH  Standard mode rate
                         *         ||||||| ||||______ RXINV RX idle state is 1
                         *         ||||||| |||_______ ABAUD Baud rate measure disabled
                         *         ||||||| ||________ LPBACK UART loop back disabled
                         *         ||||||| |_________ WAKE  No wake-up enabled
                         *         |||||||___________ UEN   TX, RX enable, CTS, RTS/BCLK controlled by port latches
                         *         ||||||
                         *         |||||_____________ RTSMD  RTS in Flow Control mode
                         *         ||||______________ IREN   IrDA disabled
                         *         |||_______________ USIDL  Continue module operation in Idle mode
                         *         ||
                         *         |_________________ UARTEN UART enable
                         * 
                         */
    return ret;
}
ssize_t drv_uart_read(void *drv, void* buf, size_t count){
    ssize_t ret = -1;
    return ret;
}
ssize_t drv_uart_write(void *drv, const void* buf, size_t count){
    ssize_t ret = -1;
    char* p = (char*)buf;
    struct DRV_UART* _drv;
    int i;
    unsigned int base_reg;
    
    _drv = container_of(drv, struct DRV_UART, drv);
    if(_drv->index < 0 || _drv->index > UART_MODULE_COUNT)
        return ret;
    base_reg = UART_REG_BASE_ADDR + (UART_REG_MODULE_LEN * _drv->index);
    
    for(i = 0; i < count; i++){
        while((REG(base_reg + UART_REG_STA) & ((unsigned int)0x01 << 8)) == 0){
            Nop();
        }
        REG(base_reg + UART_REG_TXREG) = p[i];
    }
    ret = count;
    return ret;    
}
int drv_uart_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    struct termios2 *opt;
    struct DRV_UART* _drv;
    UINT32 u32Val;
    unsigned int base_reg;

    _drv = container_of(drv, struct DRV_UART, drv);
    if(_drv->index < 0 || _drv->index > UART_MODULE_COUNT)
        return ret;
    base_reg = UART_REG_BASE_ADDR + (UART_REG_MODULE_LEN * _drv->index);
    if(request == TCGETS2){
        opt = (struct termios2*)arguments;
        memset(opt, 0, sizeof(struct termios2));
        ret = 0;
    }else if(request == TCSETS2){
        opt = (struct termios2*)arguments;
        if((REG(base_reg+UART_REG_MODE) & ((unsigned int)0x01 << 3)) != 0)
            u32Val = _drv->Fcy / 4 / opt->c_ispeed - 1;
        else 
            u32Val = _drv->Fcy / 16 / opt->c_ispeed - 1;
        REG(base_reg + UART_REG_BRG) = (unsigned int)u32Val & 0xffff;
        ret = 0;
    }else if(request == UART_IOCTL_SET_FCY){
        u32Val = *((UINT32*)arguments);
        _drv->Fcy = u32Val;
        ret = 0;
    }
    return ret;
}
#define DRV_UART_MODULE_CNT    1
const char          *g_uart_name[DRV_UART_MODULE_CNT] = {"uart0"};
struct DRV_UART     g_uart[DRV_UART_MODULE_CNT] = {
    {
      .Fcy = 8000000L,
      .index            = 0,  
      .drv.opt.open     = drv_uart_open,
      .drv.opt.close    = drv_uart_close,
      .drv.opt.read     = drv_uart_read,
      .drv.opt.write    = drv_uart_write,
      .drv.opt.ioctl    = drv_uart_ioctl,
    },
};
int drv_uartInitialize(){
    int ret = 0, i;  
    
    for(i = 0; i < DRV_UART_MODULE_CNT; i++){
        g_uart[i].drv.name = g_uart_name[i];
        drv_register(&g_uart[i].drv);
    }
    return ret;
}
// end of file
