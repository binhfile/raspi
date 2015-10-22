/* 
 * File:   drv_common.h
 * Author: dev
 *
 * Created on October 20, 2015, 12:30 PM
 */

#ifndef DRV_COMMON_H
#define	DRV_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "../../drv_api.h"
    
int drv_common_init();
    
/*--- ioctl ----*/
#define COMMON_IOCTL_SET_OSC_FREQ    0x01    // arg=&COMMON_SET_OSC
    
UINT32 drv_commonGetFRCFreq();
UINT32 drv_commonGetPrimaryFreq();
UINT32 drv_commonGetSecondaryFreq();
UINT32 drv_commonGetLowpowerFreq();

struct COMMON_SET_OSC{
    UINT32      frc;
    UINT32      primary;
    UINT32      secondary;
    UINT32      low_power;
};
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_COMMON_H */

