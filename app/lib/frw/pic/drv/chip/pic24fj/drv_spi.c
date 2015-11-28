#include "drv_spi.h"
#include "drv_regs.h"
#include "drv_perimap.h"
#include "drv_utils.h"
#include "drv_gpio.h"
#include "../../drv_api.h"
#include <frw_string.h>
#include <lib_debug.h>
#include <xc.h>
#include <ucos_ii.h>

struct DRV_SPI{
    DRV_ELEM    drv;
    int         index;
    struct spi_ioc_transfer xfer;
    unsigned int xfer_tx_cnt;
    unsigned int xfer_rx_cnt;
    unsigned int xfer_wait_tx_done;
    int 		cs_gpio_handle;
    int			cs_gpio_pin;
};
OS_FLAG_GRP* g_drv_spi_flags = 0;
int drv_spi_init();
__prog__ unsigned int g_drv_spi_clock_scale[4][8] __attribute__((space(prog)))= {
		{64*8, 64*7, 64*6, 64*5, 64*4, 64*3, 64*2, 64*1},
		{16*8, 16*7, 16*6, 16*5, 16*4, 16*3, 16*2, 16*1},
		{4*8, 4*7, 4*6, 4*5, 4*4, 4*3, 4*2, 4*1},
		{1*8, 1*7, 1*6, 1*5, 1*4, 1*3, 1*2, 1*1},
};
int drv_spi_open(void *drv, int flags){
    int ret = -1;
    struct DRV_SPI* _drv;
    unsigned int base_reg;
    
    _drv = container_of(drv, struct DRV_SPI, drv);
    if(_drv->index < 0 || _drv->index > DRV_SPI_MODULE_COUNT)
        return ret;
    base_reg = SPI_REG_BASE_ADDR + SPI_REG_MODULE_LEN * _drv->index;
    switch(_drv->index){
    case 0:
    	IFS0bits.SPI1IF = 0;
    	IEC0bits.SPI1IE = 1;
    	IPC2bits.SPI1IP = 2;
    	break;
    case 1:
    	IFS2bits.SPI2IF = 0;
    	IEC2bits.SPI2IE = 1;
    	IPC8bits.SPI2IP = 2;
    	break;
    case 2:
    	IFS5bits.SPI3IF = 0;
    	IEC5bits.SPI3IE = 1;
    	IPC22bits.SPI3IP = 2;
    	break;
    }
    /**
     * scale = 64 * 8
     * master mode
     *
     */
    REG(base_reg+SPI_REG_CON1) = \
    		((unsigned int)0x00 << 0) |	/*0-scale = 64*8 */
    		((unsigned int)0x01 << 5) |	/*1-master mode*/
			((unsigned int)0x00 << 6) |	/*clock polarity*/
			((unsigned int)0x00 << 7) |	/*1-slave select enable*/
			((unsigned int)0x00 << 8) |	/*clock edge select*/
			((unsigned int)0x01 << 9) |	/*1-data input sample at end of data output time*/
			((unsigned int)0x00 << 10) |/*0-8 bits word*/
			((unsigned int)0x00 << 11) |/*0-SDO pin is controlled by the module*/
			((unsigned int)0x00 << 12); /*0-SPI clock internal enable*/
    REG(base_reg+SPI_REG_CON2) = \
    		((unsigned int)0x01 << 0) |	/*1-Enhanced buffer enable*/
			((unsigned int)0x00 << 1) |	/*0-Frame sync pulse precedes first bit clock*/
			((unsigned int)0x00 << 13)|	/*0-Frame sync pulse is active-low*/
			((unsigned int)0x00 << 14)|	/*0-Frame sync pulse output*/
			((unsigned int)0x00 << 15);	/*0-Frame SPI suppord is enable*/
    REG(base_reg+SPI_REG_STAT) = \
    		((unsigned int)0x05 << 2) |	/*interrupt type*/
			((unsigned int)0x01 << 15);	/*Enable module*/
    ret = 0;
    LREP("CON1=%04X %04X\r\n", SPI1CON1, OSCCON);
    LREP("open %d\r\n", _drv->index);
    return ret;
}
int drv_spi_close(void *drv){
    int ret = -1;
    struct DRV_SPI* _drv;
    unsigned int base_reg;
    
    _drv = container_of(drv, struct DRV_SPI, drv);
    if(_drv->index < 0 || _drv->index > DRV_SPI_MODULE_COUNT)
        return ret;
    base_reg = SPI_REG_BASE_ADDR + SPI_REG_MODULE_LEN * _drv->index;
    switch(_drv->index){
    case 0:
    	IEC0bits.SPI1IE = 0;
    	break;
    case 1:
    	IEC2bits.SPI2IE = 0;
    	break;
    case 2:
    	IEC5bits.SPI3IE = 0;
    	break;
    }
    REG(base_reg+SPI_REG_STAT) = 0x00;/*disable module*/
    ret = 0;
    return ret;
}
ssize_t drv_spi_read(void *drv, void* buf, size_t count){
    ssize_t ret = -1;
    return ret;
}
ssize_t drv_spi_write(void *drv, const void* buf, size_t count){
    ssize_t ret = -1;

    return ret;    
}
inline int drv_spi_set_bits_per_word(void* drv, unsigned int bits_per_word){
	int ret = -1;
    struct DRV_SPI* _drv;
    unsigned int base_reg;
    _drv = container_of(drv, struct DRV_SPI, drv);
    base_reg = SPI_REG_BASE_ADDR + SPI_REG_MODULE_LEN * _drv->index;
	if(bits_per_word == 8){
		REG(base_reg+SPI_REG_CON1) =
				REG(base_reg+SPI_REG_CON1) & (~((unsigned int)0x00 << 10));
		ret = 0;
	}else if(bits_per_word == 16){
		REG(base_reg+SPI_REG_CON1) =
				REG(base_reg+SPI_REG_CON1) | (((unsigned int)0x00 << 10));
		ret = 0;
	}
	return ret;
}
inline int drv_spi_set_speed(void* drv, unsigned long long speed){
	int ret = -1;
    struct DRV_SPI* _drv;
    unsigned int base_reg;
    UINT32 val;
    unsigned int i, j, k, diff, diff2;
    unsigned int scale_pri, scale_sec;

    if(speed == 0) return ret;

    _drv = container_of(drv, struct DRV_SPI, drv);
    base_reg = SPI_REG_BASE_ADDR + SPI_REG_MODULE_LEN * _drv->index;
	val = drv_getCpuClockFreq();
	scale_pri = 0;
	scale_sec = 0;
	k = val / speed;
	diff = k > g_drv_spi_clock_scale[0][0] ? k - g_drv_spi_clock_scale[0][0] : g_drv_spi_clock_scale[0][0] - k;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 8; j++){
			diff2 = k > g_drv_spi_clock_scale[i][j] ? k - g_drv_spi_clock_scale[i][j] : g_drv_spi_clock_scale[i][j] - k;
			if(diff2 < diff){
				diff = diff2;
				scale_pri = i;
				scale_sec = j;
			}
		}
	REG(base_reg+SPI_REG_CON1) = (REG(base_reg+SPI_REG_CON1) & (~(unsigned int)0b00011111)) |
			(scale_pri & 0x03) | ((scale_sec & 0x07) << 2);
	ret = 0;
	return ret;
}
int drv_spi_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    struct DRV_SPI* _drv;
    unsigned int base_reg;
    unsigned int* pival;
    unsigned long long* plval;
    INT8U  err;
    struct spi_ioc_map_pin *map;
    struct spi_ioc_transfer* xfer;
    unsigned char *pu8;
    struct DRV_GPIO_WRITE  gpio_write;
    struct DRV_GPIO_ENABLE gpio_enable;

//#if OS_CRITICAL_METHOD == 3u                               /* Allocate storage for CPU status register */
//    OS_CPU_SR  cpu_sr = 0u;
//#endif
//    unsigned char *tx,*rx;

    _drv = container_of(drv, struct DRV_SPI, drv);
    if(_drv->index < 0 || _drv->index > UART_MODULE_COUNT)
        return ret;
    base_reg = SPI_REG_BASE_ADDR + SPI_REG_MODULE_LEN * _drv->index;
    switch(request){
		case SPI_IOC_MESSAGE(1):{
#if 1
//			OS_ENTER_CRITICAL();
			xfer = (struct spi_ioc_transfer*)arguments;
			_drv->xfer.bits_per_word 	= xfer->bits_per_word;
			_drv->xfer.len 				= xfer->len;
			_drv->xfer.rx_buf 			= xfer->rx_buf;
			_drv->xfer.tx_buf			= xfer->tx_buf;
			_drv->xfer.speed_hz 		= xfer->speed_hz;
			_drv->xfer.timeout 			= xfer->timeout;
			_drv->xfer_tx_cnt = 0;
			_drv->xfer_rx_cnt = 0;
			_drv->xfer_wait_tx_done = 0;
			drv_spi_set_bits_per_word(drv, _drv->xfer.bits_per_word);
			drv_spi_set_speed(drv, _drv->xfer.speed_hz);
//			OS_EXIT_CRITICAL();
			LREP("CON1=%04X\r\n", SPI1CON1);
			LREP("xfer %d\r\n", _drv->index);
			if(_drv->xfer.len > 0){
				pu8 = (unsigned char*)_drv->xfer.tx_buf;
				_drv->xfer_tx_cnt ++;

		    	gpio_write.pin = _drv->cs_gpio_pin;
		    	gpio_write.value = DRV_GPIO_LOW;
		    	ioctl(_drv->cs_gpio_handle, DRV_GPIO_IOCTL_WRITE, &gpio_write);

				REG(base_reg + SPI_REG_BUF) = *pu8;
				if(_drv->xfer.len > 1){
					OSFlagPend(g_drv_spi_flags,
							((unsigned int)1 << _drv->index),
							OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME,
							_drv->xfer.timeout,
							&err);
					if(err == OS_ERR_NONE)
						ret = _drv->xfer_tx_cnt;
					else{
					}
				}else{
					ret = 1;
				}

		    	gpio_write.pin = _drv->cs_gpio_pin;
		    	gpio_write.value = DRV_GPIO_HIGH;
		    	ioctl(_drv->cs_gpio_handle, DRV_GPIO_IOCTL_WRITE, &gpio_write);

			}else{
				ret = 0;
			}
#else
			OS_ENTER_CRITICAL();
			xfer = (struct spi_ioc_transfer*)arguments;
			_drv->xfer.bits_per_word 	= xfer->bits_per_word;
			_drv->xfer.len 				= xfer->len;
			_drv->xfer.rx_buf 			= xfer->rx_buf;
			_drv->xfer.tx_buf			= xfer->tx_buf;
			_drv->xfer.speed_hz 		= xfer->speed_hz;
			_drv->xfer.timeout 			= xfer->timeout;
			_drv->xfer_tx_cnt = 0;
			_drv->xfer_rx_cnt = 0;
			_drv->xfer_wait_tx_done = 0;
			drv_spi_set_bits_per_word(drv, _drv->xfer.bits_per_word);
			drv_spi_set_speed(drv, _drv->xfer.speed_hz);

			tx = (unsigned char*)_drv->xfer.tx_buf;
			rx = (unsigned char*)_drv->xfer.rx_buf;
			while(_drv->xfer.len > 0){
				REG(base_reg + SPI_REG_BUF) = *tx;
				while(SPI1STATbits.SRMPT == 0){
					Nop();
				}
				*rx = REG(base_reg + SPI_REG_BUF);
				tx++;
				rx++;
				_drv->xfer.len --;
			}
			ret = xfer->len;
			OS_EXIT_CRITICAL();
#endif
			break;
		}
		case SPI_IOC_WR_MODE:{
			pival = (unsigned int*)arguments;
			if((*pival & 0x03) == SPI_MODE_0){
				// CPOL=0 the base value of the clock is zero,i.e. the active state is 1 and idle state is 0.
				// CPHA=0, data are captured on the clock's rising edge (low→high transition)
				// and data is output on a falling edge (high→low clock transition).
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) & (~((unsigned int)0x01 << 6));
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) | ( ((unsigned int)0x01 << 8));
				ret = 0;
			}else if((*pival & 0x03) == SPI_MODE_1){
				// CPOL=0 the base value of the clock is zero,i.e. the active state is 1 and idle state is 0.
				// CPHA=1, data are captured on the clock's falling edge and data is output on a rising edge.
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) & (~(((unsigned int)0x01 << 6) | ((unsigned int)0x01 << 8) ));
				ret = 0;
			}else if((*pival & 0x03) == SPI_MODE_2){
				// CPOL=1 the base value of the clock is one (inversion of CPOL=0), i.e. the active state is 0 and idle state is 1.
				// CPHA=0, data are captured on clock's falling edge and data is output on a rising edge.
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) | (((unsigned int)0x01 << 6));
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) | (((unsigned int)0x01 << 8));
				ret = 0;
			}else if((*pival & 0x03) == SPI_MODE_3){
				// CPOL=1 the base value of the clock is one (inversion of CPOL=0), i.e. the active state is 0 and idle state is 1.
				// CPHA=1, data are captured on clock's rising edge and data is output on a falling edge
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) | (((unsigned int)0x01 << 6));
				REG(base_reg+SPI_REG_CON1) = REG(base_reg+SPI_REG_CON1) & (~((unsigned int)0x01 << 8));
				ret = 0;
			}
			DRV_UNLOCK_REG;
			SPI1CON1 = 0x0260;
			Nop();
			LREP("CON1=%04X %04X\r\n", SPI1CON1, OSCCON);
			LREP("ioctl %d\r\n", _drv->index);
			break;
		}
		case SPI_IOC_WR_LSB_FIRST:{
			break;
		}
		case SPI_IOC_WR_BITS_PER_WORD:{
			pival = (unsigned int*)arguments;
			ret = drv_spi_set_bits_per_word(drv, *pival);
			break;
		}
		case SPI_IOC_WR_MAX_SPEED_HZ:{
			plval = (unsigned long long*)arguments;
			ret = drv_spi_set_speed(drv, *plval);
			break;
		}
		case SPI_IOC_WR_MAP_PIN:{
			map = (struct spi_ioc_map_pin*)arguments;
		    switch(_drv->index){
		    case 0:
		    	DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_SDI1, map->sdi);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SDO1, map->sdo);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SCK1OUT, map->sck);
//		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SS1OUT, map->ss);
		    	_drv->cs_gpio_pin = map->ss;
		    	_drv->cs_gpio_handle = open("gpio", 0);
		    	if(_drv->cs_gpio_handle >= 0){
		    		gpio_enable.pin = _drv->cs_gpio_pin;
		    		gpio_enable.dir = DRV_GPIO_OUTPUT;
		    		gpio_enable.opendrain = DRV_GPIO_OPEN_DRAIN_DISABLE;
		    		if(ioctl(_drv->cs_gpio_handle, DRV_GPIO_IOCTL_ENABLE, &gpio_enable) < 0){
		    			LREP("enable gpio %d failed\r\n", gpio_enable.pin);
		    		}
			    	gpio_write.pin = _drv->cs_gpio_pin;
			    	gpio_write.value = DRV_GPIO_HIGH;
			    	ioctl(_drv->cs_gpio_handle, DRV_GPIO_IOCTL_WRITE, &gpio_write);
		    	}else{
		    		LREP("open gpio failed\r\n");
		    	}
		    	ret = 0;
		    	break;
		    case 1:
		    	DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_SDI2, map->sdi);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SDO2, map->sdo);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SCK2OUT, map->sck);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SS2OUT, map->ss);
		    	ret = 0;
		    	break;
		    case 2:
		    	DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_SDI2, map->sdi);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SDO2, map->sdo);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SCK2OUT, map->sck);
		    	DRV_PERI_OUTPUT_MAP(DRV_PERIMAP_OUTPUT_SS2OUT, map->ss);
		    	ret = 0;
		    	break;
		    }
			break;
		}
    }
    return ret;
}
const char          *g_drv_spi_name[DRV_SPI_MODULE_COUNT] = {"spi1", "spi2", "spi3"};
#if (DRV_SPI_MODULE_ENABLE & 0x01)
struct DRV_SPI     g_drv_spi_0 = {
        .index            = 0,
        .drv.opt.init     = drv_spi_init,
        .drv.opt.open     = drv_spi_open,
        .drv.opt.close    = drv_spi_close,
        .drv.opt.read     = drv_spi_read,
        .drv.opt.write    = drv_spi_write,
        .drv.opt.ioctl    = drv_spi_ioctl,
};
#endif
#if (DRV_SPI_MODULE_ENABLE & 0x02)
struct DRV_SPI     g_drv_spi_1 = {
        .index            = 1,
        .drv.opt.init     = drv_spi_init,
        .drv.opt.open     = drv_spi_open,
        .drv.opt.close    = drv_spi_close,
        .drv.opt.read     = drv_spi_read,
        .drv.opt.write    = drv_spi_write,
        .drv.opt.ioctl    = drv_spi_ioctl,
};
#endif
#if (DRV_SPI_MODULE_ENABLE & 0x04)
struct DRV_SPI     g_drv_spi_2 = {
        .index            = 2,
        .drv.opt.init     = drv_spi_init,
        .drv.opt.open     = drv_spi_open,
        .drv.opt.close    = drv_spi_close,
        .drv.opt.read     = drv_spi_read,
        .drv.opt.write    = drv_spi_write,
        .drv.opt.ioctl    = drv_spi_ioctl,
};
#endif

int drv_spi_init(){
	INT8U err;
#if (DRV_SPI_MODULE_ENABLE & 0x01)
    g_drv_spi_0.drv.name      = g_drv_spi_name[0];
#endif
#if (DRV_SPI_MODULE_ENABLE & 0x02)
    g_drv_spi_1.drv.name      = g_drv_spi_name[1];
#endif
#if (DRV_SPI_MODULE_ENABLE & 0x04)
    g_drv_spi_2.drv.name      = g_drv_spi_name[2];
#endif
    if(g_drv_spi_flags == 0){
    	g_drv_spi_flags = OSFlagCreate(0, &err);
    }
    return 0;
}
#if (DRV_SPI_MODULE_ENABLE & 0x01)
DRV_REGISTER(g_drv_spi_0);
void __attribute__ ((interrupt, no_auto_psv)) _SPI1Interrupt(void){
	unsigned char* pu8;
	INT8U err;
#if OS_CRITICAL_METHOD == 3u                               /* Allocate storage for CPU status register */
    OS_CPU_SR     cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();

	IFS0bits.SPI1IF = 0;
	// rx
	pu8 = (unsigned char*)g_drv_spi_0.xfer.rx_buf;
	while(SPI1STATbits.SRXMPT == 0){
		if(g_drv_spi_0.xfer_rx_cnt < g_drv_spi_0.xfer.len){
			*(pu8 + g_drv_spi_0.xfer_rx_cnt) = SPI1BUF;
			g_drv_spi_0.xfer_rx_cnt++;
		}
	}
	// tx
	if(g_drv_spi_0.xfer_wait_tx_done == 0){
		pu8 = (unsigned char*)g_drv_spi_0.xfer.tx_buf;
		while(SPI1STATbits.SPITBF == 0){
			if(g_drv_spi_0.xfer_tx_cnt < g_drv_spi_0.xfer.len){
				SPI1BUF = *(pu8 + g_drv_spi_0.xfer_tx_cnt);
				g_drv_spi_0.xfer_tx_cnt ++;
			}else{
				if(g_drv_spi_0.xfer_wait_tx_done == 0){
					g_drv_spi_0.xfer_wait_tx_done = 1;
				}
				break;
			}
		}
	}else{
		OSFlagPost(g_drv_spi_flags, 0x01, OS_FLAG_SET, &err);
	}
	OS_EXIT_CRITICAL();
}
#endif
#if (DRV_SPI_MODULE_ENABLE & 0x02)
DRV_REGISTER(g_drv_spi_1);
void __attribute__ ((interrupt, no_auto_psv)) _SPI2Interrupt(void){
	unsigned char* pu8;
	INT8U err;
#if OS_CRITICAL_METHOD == 3u                               /* Allocate storage for CPU status register */
    OS_CPU_SR     cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();

	IFS2bits.SPI2IF = 0;
	// rx
	pu8 = (unsigned char*)g_drv_spi_1.xfer.rx_buf;
	while(SPI2STATbits.SRXMPT == 0){
		if(g_drv_spi_1.xfer_rx_cnt < g_drv_spi_1.xfer.len){
			*(pu8 + g_drv_spi_1.xfer_rx_cnt) = SPI2BUF;
			g_drv_spi_1.xfer_rx_cnt++;
		}
	}
	// tx
	if(g_drv_spi_1.xfer_wait_tx_done == 0){
		pu8 = (unsigned char*)g_drv_spi_1.xfer.tx_buf;
		while(SPI2STATbits.SPITBF == 0){
			if(g_drv_spi_1.xfer_tx_cnt < g_drv_spi_1.xfer.len){
				SPI2BUF = *(pu8 + g_drv_spi_1.xfer_tx_cnt);
				g_drv_spi_1.xfer_tx_cnt ++;
			}else{
				if(g_drv_spi_1.xfer_wait_tx_done == 0){
					g_drv_spi_1.xfer_wait_tx_done = 1;
				}
				break;
			}
		}
	}else{
		OSFlagPost(g_drv_spi_flags, 0x02, OS_FLAG_SET, &err);
	}
	OS_EXIT_CRITICAL();
}
#endif
#if (DRV_SPI_MODULE_ENABLE & 0x04)
DRV_REGISTER(g_drv_spi_2);
void __attribute__ ((interrupt, no_auto_psv)) _SPI3Interrupt(void){
	unsigned char* pu8;
	INT8U err;
#if OS_CRITICAL_METHOD == 3u                               /* Allocate storage for CPU status register */
    OS_CPU_SR     cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();

	IFS5bits.SPI3IF = 0;
	// rx
	pu8 = (unsigned char*)g_drv_spi_2.xfer.rx_buf;
	while(SPI3STATbits.SRXMPT == 0){
		if(g_drv_spi_2.xfer_rx_cnt < g_drv_spi_2.xfer.len){
			*(pu8 + g_drv_spi_2.xfer_rx_cnt) = SPI3BUF;
			g_drv_spi_2.xfer_rx_cnt++;
		}
	}
	// tx
	if(g_drv_spi_2.xfer_wait_tx_done == 0){
		pu8 = (unsigned char*)g_drv_spi_2.xfer.tx_buf;
		while(SPI3STATbits.SPITBF == 0){
			if(g_drv_spi_2.xfer_tx_cnt < g_drv_spi_2.xfer.len){
				SPI3BUF = *(pu8 + g_drv_spi_2.xfer_tx_cnt);
				g_drv_spi_2.xfer_tx_cnt ++;
			}else{
				if(g_drv_spi_2.xfer_wait_tx_done == 0){
					g_drv_spi_2.xfer_wait_tx_done = 1;
				}
				break;
			}
		}
	}else{
		OSFlagPost(g_drv_spi_flags, 0x04, OS_FLAG_SET, &err);
	}
	OS_EXIT_CRITICAL();
}
#endif



// end of file
