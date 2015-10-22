#ifndef DRV_REGS_H__
#define DRV_REGS_H__
#define REG(x)  (*((volatile unsigned int*)(x)))
/*--- UART ---*/
#define UART_MODULE_COUNT       4
#define UART_REG_BASE_ADDR      0x0220
#define UART_REG_MODULE_LEN     0x0010
#define UART_REG_MODE           0x00
#define UART_REG_STA            0x02
#define UART_REG_TXREG          0x04
#define UART_REG_RXREG          0x06
#define UART_REG_BRG            0x08
/*--- MAP PIN ---*/
#define RPIN_REG_BASE_ADDRESS    0x0680
#define RPO_REG_BASE_ADDRESS     0x06C0
/*--- GPIO ----*/
#define GPIO_REG_BASE_ADDR      0x02C0
#define GPIO_REG_MODULE_LEN     0x08
#define GPIO_REG_TRIS           0x00
#define GPIO_REG_PORT           0x02
#define GPIO_REG_LAT            0x04
#define GPIO_REG_ODC            0x06
/*--- ADC ---*/
#define ADC_REG_BASE_ADDR       0x0300
#define ADC_REG_AD1PCFGL        0x002C
/*---- ICN ----*/
#define ICN_REG_BASE_ADDR       0x0054
#define ICN_REG_CNPD            0x00
#define ICN_REG_CNEN            0x0C
#define ICN_REG_CNPU            0x18
#endif
