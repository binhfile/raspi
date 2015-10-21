#include "drv_uart.h"
#include "drv_regs.h"
#include "drv_perimap.h"
#include "drv_utils.h"
#include "../../drv_api.h"
#include <frw_string.h>
#include <xc.h>

struct DRV_UART{
    DRV_ELEM    drv;
    int         index;
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
//    REG(base_reg + UART_REG_BRG)  = 25;// Default 9600@8Mhz 
    // Map pin
//    RPINR18bits.U1RXR   = 6;    // RP6
//    RPOR3bits.RP7R      = 3;    // RP7
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
    struct UART_MAP_PIN *map_pin;
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
            u32Val = drv_getCpuClockFreq() / 4 / opt->c_ispeed - 1;
        else 
            u32Val = drv_getCpuClockFreq() / 16 / opt->c_ispeed - 1;
        REG(base_reg + UART_REG_BRG) = (unsigned int)u32Val & 0xffff;
        ret = 0;
    }else if(request == UART_IOCTL_MAP_PIN){
        map_pin = (struct UART_MAP_PIN*)arguments;
        ret = 0;
        DRV_UNLOCK_REG;
        if(_drv->index == 0){
            DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_U1RX, map_pin->rx);
            DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_U1TX, map_pin->tx);
        }else if(_drv->index == 1){
            DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_U2RX, map_pin->rx);
            DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_U2TX, map_pin->tx);
        }else if(_drv->index == 2){
            DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_U3RX, map_pin->rx);
            DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_U3TX, map_pin->tx);
        }else if(_drv->index == 3){
            DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_U4RX, map_pin->rx);
            DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_U4TX, map_pin->tx);
        }else ret = -1;
        DRV_LOCK_REG;
    }
    return ret;
}
#define DRV_UART_MODULE_CNT    4
const char          *g_uart_name[DRV_UART_MODULE_CNT] = {"uart0", "uart1", "uart2", "uart3"};
struct DRV_UART     g_uart_0 = {
        .index            = 0,
        .drv.opt.open     = drv_uart_open,
        .drv.opt.close    = drv_uart_close,
        .drv.opt.read     = drv_uart_read,
        .drv.opt.write    = drv_uart_write,
        .drv.opt.ioctl    = drv_uart_ioctl,
};
void drv_uartInitialize(){   
    g_uart_0.drv.name         = g_uart_name[0];
    drv_register(&g_uart_0.drv);
}
DRV_INIT(drv_uartInitialize);
DRV_OPTS(g_uart_0);
//DRV_OPTS(g_uart_1);
//DRV_OPTS(g_uart_2);
//DRV_OPTS(g_uart_3);
//drv_init_fxn drv_uart_init __attribute__((__section__(".drv_init"))) = drv_uartInitialize;
// end of file
