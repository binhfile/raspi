#include "drv_common.h"
typedef struct {
    UINT32      frc;
    UINT32      primary;
    UINT32      secondary;
    UINT32      low_power;
}DRV_COMMON_OSC;
struct DRV_COMMON{
    DRV_ELEM    drv;
    DRV_COMMON_OSC  osc;
};

int drv_common_open(void *drv, int flags){
    return -1;
}
int drv_common_close(void *drv){
    return -1;
}
ssize_t drv_common_read(void *drv, void* buf, size_t count){
    return -1;
}
ssize_t drv_common_write(void *drv, const void* buf, size_t count){
    return -1;    
}
int drv_common_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    struct DRV_COMMON* _drv;
    struct COMMON_SET_OSC *set_osc;

    _drv = container_of(drv, struct DRV_COMMON, drv);
    if(request == COMMON_IOCTL_SET_OSC_FREQ){
        set_osc = (struct COMMON_SET_OSC*)arguments;
        _drv->osc.frc       = set_osc->frc;
        _drv->osc.low_power = set_osc->low_power;
        _drv->osc.primary   = set_osc->primary;
        _drv->osc.secondary = set_osc->secondary;
        ret = 0;
    }
    return ret;
}
const char            g_common_name[] = "common";
struct DRV_COMMON     g_common = {
    .osc.frc          = 0,  
    .osc.low_power    = 0,  
    .osc.primary      = 0,  
    .osc.secondary    = 0,                
    .drv.opt.open     = drv_common_open,
    .drv.opt.close    = drv_common_close,
    .drv.opt.read     = drv_common_read,
    .drv.opt.write    = drv_common_write,
    .drv.opt.ioctl    = drv_common_ioctl,
};
int drv_commonInitialize(){
    g_common.drv.name = g_common_name;
    drv_register(&g_common.drv);
    return 0;
}
UINT32 drv_commonGetFRCFreq(){
    return g_common.osc.frc;
}
UINT32 drv_commonGetPrimaryFreq(){
    return g_common.osc.primary;
}
UINT32 drv_commonGetSecondaryFreq(){
    return g_common.osc.secondary;
}
UINT32 drv_commonGetLowpowerFreq(){
    return g_common.osc.low_power;
}
// end of file
