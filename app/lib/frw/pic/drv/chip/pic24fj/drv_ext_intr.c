#include "drv_ext_intr.h"
#include "drv_regs.h"
#include "../../drv_api.h"
#include "../../../frw_string.h"
#include <xc.h>
struct DRV_EXT_INTR{
    DRV_ELEM drv;
    int index;
};
int drv_ext_intr_init();
int drv_ext_intr_open(void *drv, int flags);
int drv_ext_intr_close(void *drv);
int drv_ext_intr_ioctl(void *drv, int request, unsigned int arguments);

const char      *g_drv_ext_intr_name[] = {
    "ext_intr_0",
    "ext_intr_1",
    "ext_intr_2",
    "ext_intr_3",
    "ext_intr_4"
};
struct DRV_EXT_INTR g_drv_ext_intr_0 = {
    .index = 0,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl
};
DRV_REGISTER(g_drv_ext_intr_0);
#if (DRV_USE_EXT_INTR_1 == 1)
struct DRV_EXT_INTR g_drv_ext_intr_1 = {
    .index = 1,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl
};
DRV_REGISTER(g_drv_ext_intr_1);
#endif
#if (DRV_USE_EXT_INTR_2 == 1)
struct DRV_EXT_INTR g_drv_ext_intr_2 = {
    .index = 2,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl
};
DRV_REGISTER(g_drv_ext_intr_2);
#endif
#if (DRV_USE_EXT_INTR_3 == 1)
struct DRV_EXT_INTR g_drv_ext_intr_3 = {
    .index = 3,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl
};
DRV_REGISTER(g_drv_ext_intr_3);
#endif
#if (DRV_USE_EXT_INTR_4 == 1)
struct DRV_EXT_INTR g_drv_ext_intr_4 = {
    .index = 4,
    .drv.opt.init   = drv_ext_intr_init,
    .drv.opt.open   = drv_ext_intr_open,
    .drv.opt.close  = drv_ext_intr_close,
    .drv.opt.ioctl  = drv_ext_intr_ioctl
};
DRV_REGISTER(g_drv_ext_intr_4);
#endif
int drv_ext_intr_init(){
    g_drv_ext_intr_0.drv.name = g_drv_ext_intr_name[0];
    #if (DRV_USE_EXT_INTR_1 == 1)
    g_drv_ext_intr_1.drv.name = g_drv_ext_intr_name[1];
    #endif
    #if (DRV_USE_EXT_INTR_4 == 1)
    g_drv_ext_intr_2.drv.name = g_drv_ext_intr_name[2];
    #endif
    #if (DRV_USE_EXT_INTR_4 == 1)
    g_drv_ext_intr_3.drv.name = g_drv_ext_intr_name[3];
    #endif
    #if (DRV_USE_EXT_INTR_4 == 1)
    g_drv_ext_intr_4.drv.name = g_drv_ext_intr_name[4];
    #endif
    return 0;
}
int drv_ext_intr_open(void *drv, int flags){
    int ret = -1;
    struct DRV_EXT_INTR *_drv;
    
    _drv = container_of(drv, struct DRV_EXT_INTR, drv);
    return ret;
}
int drv_ext_intr_close(void *drv){
    return 0;
}
int drv_ext_intr_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    
    return ret;
}
// end of file

