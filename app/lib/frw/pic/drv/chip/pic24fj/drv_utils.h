/* 
 * File:   drv_utils.h
 * Author: dev
 *
 * Created on October 20, 2015, 12:18 PM
 */

#ifndef DRV_UTILS_H
#define	DRV_UTILS_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "../../drv_api.h"
    
#define  DRV_FRCDIV_MASK                (UINT16)(7 <<  8)
#define  DRV_PLLPOST_MASK               (UINT16)(3 <<  6)
#define  DRV_PLLPRE_MASK                (UINT16)(0x1F <<  0)
#define  DRV_PLLDIV_MASK                (UINT16)(0xFF <<  0)
#define  DRV_COSC_MASK                  (UINT16)(7 << 12)

#define DRV_UNLOCK_REG  {OSCCONbits.IOLOCK = 0;}
#define DRV_LOCK_REG  {OSCCONbits.IOLOCK = 1;}
    
#define DRV_PIN_RP(x)   (x)

UINT32  drv_getCpuClockFreq (void);
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_UTILS_H */

