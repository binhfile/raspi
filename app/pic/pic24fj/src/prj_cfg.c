#include <xc.h>
#include "prj_cfg.h"
#include <drv/drv_api.h>
#include "drv/chip/pic24fj/drv_gpio.h"
#include <drv/chip/pic24fj/drv_uart.h>
#include <drv/chip/pic24fj/drv_ext_intr.h>
#include <drv/chip/pic24fj/drv_common.h>
#include <drv/chip/pic24fj/drv_utils.h>
#include <drv/chip/pic24fj/drv_spi.h>
#include <lib_debug.h>
#include <os_cfg.h>

#include <en25f80/en25f80.h>

int g_fd_uart0 = -1;
int g_fd_gpio  = -1;
int g_fd_ext_intr_1 = -1;
int g_fd_spi_1 = -1;

int g_fd_flash = -1;

void App_Error(){
    TRISEbits.TRISE6 = 0;
    while(1){
        LATEbits.LATE6 = 0;
    }
}
#include <drv/chip/pic24fj/drv_common.h>
void App_Initialize(){
    struct termios2 opt;
    struct UART_MAP_PIN map_pin;
    struct COMMON_SET_OSC osc;
    struct DRV_GPIO_ENABLE gpio_enable;
    struct DRV_GPIO_WRITE  gpio_write;
    struct DRV_EXT_INTR_MAP_PIN ext_intr_map;
    struct DRV_EXT_INTR_CFG ext_intr_cfg;
    unsigned int mode;
    unsigned int bits;
    unsigned long long speed;
    struct spi_ioc_map_pin spi_map;

    int fd;

    drv_initialize();   // Load all driver is link
    // Common DRV
    osc.frc         = 8000000L;
    osc.primary     = 25000000L;
    osc.secondary   = 25000000L;
    osc.low_power   = 31000L;
    fd = drv_findFdByName("common");
    ioctl(fd, COMMON_IOCTL_SET_OSC_FREQ, &osc);
    // UART DRV
    g_fd_uart0 = open("uart0", 0);
    if(g_fd_uart0 < 0) App_Error();
    ioctl(g_fd_uart0, TCGETS2, &opt);
    opt.c_ispeed = 115200;
    opt.c_ospeed = 115200;
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_cflag &= ~CSTOPB;
    opt.c_cflag &= ~PARENB;
    opt.c_iflag &= ~INPCK;
    ioctl(g_fd_uart0, TCSETS2, &opt);
    map_pin.rx = UART_RX_PIN;
    map_pin.tx = UART_TX_PIN;
    ioctl(g_fd_uart0, UART_IOCTL_MAP_PIN, &map_pin);
    // GPIO
    g_fd_gpio = open("gpio", 0);
    if(g_fd_gpio < 0) LREP("open gpio failed\r\n");
    else{
        gpio_enable.pin = LED_STATUS;
        fd = ioctl(g_fd_gpio, DRV_GPIO_IOCTL_ENABLE, &gpio_enable);
        gpio_write.pin = LED_STATUS;
        gpio_write.value = DRV_GPIO_LOW;
        fd = ioctl(g_fd_gpio, DRV_GPIO_IOCTL_WRITE, &gpio_write);

        gpio_enable.pin = RESET_PIN;
		gpio_enable.dir = DRV_GPIO_OUTPUT;
		gpio_enable.opendrain = DRV_GPIO_OPEN_DRAIN_DISABLE;
		fd = ioctl(g_fd_gpio, DRV_GPIO_IOCTL_ENABLE, &gpio_enable);
		if(fd != 0){
			LREP("enable gpio %d failed\r\n", RESET_PIN);
		}
    }
    // External interrupt
    g_fd_ext_intr_1 = open("ext_intr_1", 0);
    if(g_fd_ext_intr_1 < 0) LREP("open external interrupt failed\r\n");
    else{
    	ext_intr_cfg.intr_type = DRV_EXT_INTR_RISING;
    	ext_intr_cfg.prio      = 2;
    	fd = ioctl(g_fd_ext_intr_1, DRV_EXT_INTR_IOCTL_CFG, &ext_intr_cfg);
    	if(fd != 0) LREP("config external interrupt failed\r\n");
    	ext_intr_map.rpin 	   = EXT_INTR_PIN;//
    	fd = ioctl(g_fd_ext_intr_1, DRV_EXT_INTR_IOCTL_MAP_PIN, &ext_intr_map);
    	if(fd != 0) LREP("map external interrupt failed\r\n");
    }
    // spi
//    g_fd_spi_1 = open("spi1", 0);
//    if(g_fd_spi_1 < 0) LREP("open spi device\r\n");
//    else{
//    	mode = SPI_MODE_0;
//    	bits = 8;
//    	speed = 1000000L;
//    	spi_map.sck = SPI_SCK_PIN;
//    	spi_map.sdi = SPI_SDI_PIN;
//    	spi_map.sdo = SPI_SDO_PIN;
//    	spi_map.ss  = SPI_SS_PIN;
//
//    	fd = ioctl(g_fd_spi_1, SPI_IOC_WR_MODE, &mode);
//    	if (fd == -1)
//    		LREP("can't set spi mode\r\n");
//    	/*
//    	 * bits per word
//    	 */
//    	fd = ioctl(g_fd_spi_1, SPI_IOC_WR_BITS_PER_WORD, &bits);
//    	if (fd == -1)
//    		LREP("can't set bits per word\r\n");
//    	/*
//    	 * max speed hz
//    	 */
//    	fd = ioctl(g_fd_spi_1, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
//    	if (fd == -1)
//    		LREP("can't set max speed hz\r\n");
//    	fd = ioctl(g_fd_spi_1, SPI_IOC_WR_MAP_PIN, &spi_map);
//		if (fd == -1)
//			LREP("can't map pin\r\n");
//		else{
//			DRV_ADC_DISABLE_PIN(DRV_PIN_ADC(8));
//			DRV_ADC_DISABLE_PIN(DRV_PIN_ADC(9));
//			DRV_ADC_DISABLE_PIN(DRV_PIN_ADC(14));
//			DRV_ADC_DISABLE_PIN(DRV_PIN_ADC(15));
//		}
		// flash
		g_fd_flash = open("en25f80_1", 0);
//		if(g_fd_flash >= 0){
//			fd = ioctl(g_fd_flash, EN25F80_IOC_WR_SPI_FD, &g_fd_spi_1);
//	    	if (fd < 0)
//	    		LREP("can't set fd\r\n");
//		}else{
//			LREP("open flash false\r\n");
//		}
//    }
}
void frw_debugPrint(const void* sz){
    write(g_fd_uart0, sz, strlen(sz));
}

//end of file
