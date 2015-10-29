/* 
 * File:   app_cfg.h
 * Author: dev
 *
 * Created on October 19, 2015, 11:20 AM
 */

#ifndef PRJ_CFG_H
#define	PRJ_CFG_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <frw_string.h>
#include <drv/chip/pic24fj/drv_utils.h>
    
extern int g_fd_uart0;
extern int g_fd_gpio;
extern int g_fd_ext_intr_1;
extern int g_fd_spi_1;
    
#define LED_STATUS			DRV_GPIO_RE5
#define LED_ERROR			DRV_GPIO_RE6

#define UART_TX_PIN			DRV_PIN_RP(6)
#define UART_RX_PIN			DRV_PIN_RP(7)

#define RESET_PIN			DRV_PIN_RP(9)
#define EXT_INTR_PIN		DRV_PIN_RP(21)
#define SPI_SCK_PIN			DRV_PIN_RP(29)
#define SPI_SDI_PIN			DRV_PIN_RP(14)
#define SPI_SDO_PIN			DRV_PIN_RP(10)
#define SPI_SS_PIN			DRV_PIN_RP(17)

void App_Initialize();
void App_Delay(int delay);
#ifdef	__cplusplus
}
#endif

#endif	/* PRJ */

