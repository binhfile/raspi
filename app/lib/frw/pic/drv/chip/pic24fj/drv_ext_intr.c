#include "drv_ext_intr.h"
#include "drv_regs.h"
#include "drv_perimap.h"
#include "drv_utils.h"
#include "drv_gpio.h"
#include "../../drv_api.h"
#include "../../../frw_string.h"
#include <xc.h>
#include <ucos_ii.h>
struct DRV_EXT_INTR{
    DRV_ELEM drv;
    int index;
};
int drv_ext_intr_init();
int drv_ext_intr_open(void *drv, int flags);
int drv_ext_intr_close(void *drv);
int drv_ext_intr_ioctl(void *drv, int request, unsigned int arguments);
int drv_ext_intr_poll(void *drv, int timeout);

OS_FLAG_GRP		*g_drv_ext_intr_flag = 0;
const char      *g_drv_ext_intr_name[] = {
    "ext_intr_0",
    "ext_intr_1",
    "ext_intr_2",
    "ext_intr_3",
    "ext_intr_4"
};
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x01)
struct DRV_EXT_INTR g_drv_ext_intr_0 = {
    .index = 0,
	.event = 0,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl,
	.drv.opt.poll  = drv_ext_intr_poll,
};
DRV_REGISTER(g_drv_ext_intr_0);
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x02)
struct DRV_EXT_INTR g_drv_ext_intr_1 = {
    .index = 1,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl,
	.drv.opt.poll  = drv_ext_intr_poll,
};
DRV_REGISTER(g_drv_ext_intr_1);
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x04)
struct DRV_EXT_INTR g_drv_ext_intr_2 = {
    .index = 2,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl,
	.drv.opt.poll  = drv_ext_intr_poll,
};
DRV_REGISTER(g_drv_ext_intr_2);
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x08)
struct DRV_EXT_INTR g_drv_ext_intr_3 = {
    .index = 3,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl,
	.drv.opt.poll  = drv_ext_intr_poll,
};
DRV_REGISTER(g_drv_ext_intr_3);
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x10)
struct DRV_EXT_INTR g_drv_ext_intr_4 = {
    .index = 4,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl,
	.drv.opt.poll  = drv_ext_intr_poll,
};
DRV_REGISTER(g_drv_ext_intr_4);
#endif
int drv_ext_intr_init(){
	INT8U err;
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x01)
    g_drv_ext_intr_0.drv.name = g_drv_ext_intr_name[0];
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x02)
    g_drv_ext_intr_1.drv.name = g_drv_ext_intr_name[1];
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x04)
    g_drv_ext_intr_2.drv.name = g_drv_ext_intr_name[2];
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x08)
    g_drv_ext_intr_3.drv.name = g_drv_ext_intr_name[3];
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x10)
    g_drv_ext_intr_4.drv.name = g_drv_ext_intr_name[4];
#endif
    if(g_drv_ext_intr_flag == 0)
    	g_drv_ext_intr_flag = OSFlagCreate(0, &err);
    return 0;
}
#include <lib_debug.h>

int drv_ext_intr_open(void *drv, int flags){
    int ret = -1;
    struct DRV_EXT_INTR *_drv;

    _drv = container_of(drv, struct DRV_EXT_INTR, drv);
    if(((unsigned char)0x01 << _drv->index) & DRV_EXT_INTR_MODULE_ENABLE){
    	switch( _drv->index){
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x01)
    	case 0:
        	IEC0bits.INT0IE = 1;
        	IPC0bits.INT0IP = 1;
        	ret = 0;
        	break;
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x02)
    	case 1:
        	IEC1bits.INT1IE = 1;
        	IPC5bits.INT1IP = 1;
        	ret = 0;
        	break;
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x04)
    	case 2:
        	IEC1bits.INT2IE = 1;
        	IPC7bits.INT2IP = 1;
        	ret = 0;
        	break;
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x08)
    	case 3:
        	IEC3bits.INT3IE = 1;
        	IPC13bits.INT3IP = 1;
        	ret = 0;
        	break;
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x10)
    	case 4:
        	IEC3bits.INT4IE = 1;
        	IPC13bits.INT4IP = 1;
        	ret = 0;
        	break;
#endif
    	}
    }
    return ret;
}
int drv_ext_intr_close(void *drv){
    int ret = -1;
    struct DRV_EXT_INTR *_drv;
#if OS_CRITICAL_METHOD == 3u                               /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr = 0u;
#endif
    OS_ENTER_CRITICAL();
    _drv = container_of(drv, struct DRV_EXT_INTR, drv);
    if(((unsigned char)0x01 << _drv->index) & DRV_EXT_INTR_MODULE_ENABLE){
    	switch( _drv->index){
    	case 0:
        	IEC0bits.INT0IE = 0;
        	ret = 0;
        	break;
    	case 1:
        	IEC1bits.INT1IE = 0;
        	ret = 0;
        	break;
    	case 2:
        	IEC1bits.INT2IE = 0;
        	ret = 0;
        	break;
    	case 3:
        	IEC3bits.INT3IE = 0;
        	ret = 0;
        	break;
    	case 4:
        	IEC3bits.INT4IE = 0;
        	ret = 0;
        	break;
    	}
    }
    OS_EXIT_CRITICAL();
    return ret;
}
int drv_ext_intr_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    struct DRV_EXT_INTR *_drv;
    struct DRV_EXT_INTR_CFG *cfg;
    struct DRV_EXT_INTR_MAP_PIN* map;

    _drv = container_of(drv, struct DRV_EXT_INTR, drv);
    if(((unsigned char)0x01 << _drv->index) & DRV_EXT_INTR_MODULE_ENABLE){
    	switch(request){
			case DRV_EXT_INTR_IOCTL_CFG:{
				cfg = (struct DRV_EXT_INTR_CFG*)arguments;
				switch(cfg->intr_type){
					case DRV_EXT_INTR_FALLING:{
						INTCON2 = INTCON2 | ((unsigned int)0x01 << _drv->index);
						ret = 0;
						break;
					}
					case DRV_EXT_INTR_RISING:{
						INTCON2 = INTCON2 & (~((unsigned int)0x01 << _drv->index));
						ret = 0;
						break;
					}
				}
				switch(_drv->index){
					case 0:
						IPC0bits.INT0IP = cfg->prio;
						ret = 0;
						break;
					case 1:
						IPC5bits.INT1IP = cfg->prio;
						ret = 0;
						break;
					case 2:
						IPC7bits.INT2IP = cfg->prio;
						ret = 0;
						break;
					case 3:
						IPC13bits.INT3IP = cfg->prio;
						ret = 0;
						break;
					case 4:
						IPC13bits.INT4IP = cfg->prio;
						ret = 0;
						break;
					}
				break;
			}//DRV_EXT_INTR_IOCTL_CFG
			case DRV_EXT_INTR_IOCTL_MAP_PIN:{
				map = (struct DRV_EXT_INTR_MAP_PIN*)arguments;
				switch(_drv->index){
					case 1:
						DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_INT1, (map->rpin));
						ret = 0;
						break;
					case 2:
						DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_INT2, (map->rpin));
						ret = 0;
						break;
					case 3:
						DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_INT3, (map->rpin));
						ret = 0;
						break;
					case 4:
						DRV_PERI_INPUT_MAP(DRV_PERIMAP_INPUT_INT4, (map->rpin));
						ret = 0;
						break;
					}
				break;
			}// DRV_EXT_INTR_IOCTL_MAP_PIN
    	}
    }
    return ret;
}
volatile int cnt = 0;
int drv_ext_intr_poll(void *drv, int timeout){
    int ret = -1;
    INT8U err = 0;
    struct DRV_EXT_INTR *_drv;

    _drv = container_of(drv, struct DRV_EXT_INTR, drv);
    if(((unsigned char)0x01 << _drv->index) & DRV_EXT_INTR_MODULE_ENABLE){
    	OSFlagPend(g_drv_ext_intr_flag, (0x01 << _drv->index), OS_FLAG_WAIT_SET_ALL + OS_FLAG_CONSUME, timeout, &err);
    	ret = err;
    }
    return ret;
}
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x01)
void __attribute__ ((interrupt, no_auto_psv)) _INT0Interrupt(void){
    IFS0bits.INT0IF = 0;
    if(g_drv_ext_intr_0.event)
    	OSMutexPost(g_drv_ext_intr_0.event);
}
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x02)
void __attribute__((__interrupt__,auto_psv)) _INT1Interrupt(){
	INT8U err;
#if OS_CRITICAL_METHOD == 3u                               /* Allocate storage for CPU status register */
    OS_CPU_SR     cpu_sr = 0u;
#endif
	OS_ENTER_CRITICAL();
    IFS1bits.INT1IF = 0;
    OSFlagPost(g_drv_ext_intr_flag, 0x02, OS_FLAG_SET, &err);
    OS_EXIT_CRITICAL();
}
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x04)
void __attribute__ ((interrupt, no_auto_psv)) _INT2Interrupt(void){
    IFS1bits.INT2IF = 0;
    if(g_drv_ext_intr_2.event)
    	OSMutexPost(g_drv_ext_intr_2.event);
}
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x08)
void __attribute__ ((interrupt, no_auto_psv)) _INT3Interrupt(void){
    IFS3bits.INT3IF = 0;
    if(g_drv_ext_intr_3.event)
    	OSMutexPost(g_drv_ext_intr_3.event);
}
#endif
#if (DRV_EXT_INTR_MODULE_ENABLE & 0x10)
void __attribute__ ((interrupt, no_auto_psv)) _INT4Interrupt(void){
    IFS3bits.INT4IF = 0;
    if(g_drv_ext_intr_4.event)
    	OSMutexPost(g_drv_ext_intr_4.event);
}
#endif
// end of file

