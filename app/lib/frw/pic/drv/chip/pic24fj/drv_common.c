#include "drv_common.h"
#include "../../../frw_string.h"

int drv_common_open(void *drv, int flags){
    return -1;
}
int drv_common_close(void *drv){
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
const char            g_drv_common_name[] = "common";
struct DRV_COMMON     g_drv_common = {
    .osc.frc          = 0,  
    .osc.low_power    = 0,  
    .osc.primary      = 0,  
    .osc.secondary    = 0,  
    .drv.opt.init     = drv_common_init,
    .drv.opt.open     = drv_common_open,
    .drv.opt.close    = drv_common_close,
    .drv.opt.ioctl    = drv_common_ioctl,
};
int drv_common_init(){
    g_drv_common.drv.name = g_drv_common_name;

    return 0;
}
DRV_REGISTER(g_drv_common);
UINT32 drv_commonGetFRCFreq(){
    return g_drv_common.osc.frc;
}
UINT32 drv_commonGetPrimaryFreq(){
    return g_drv_common.osc.primary;
}
UINT32 drv_commonGetSecondaryFreq(){
    return g_drv_common.osc.secondary;
}
UINT32 drv_commonGetLowpowerFreq(){
    return g_drv_common.osc.low_power;
}
// end of file
