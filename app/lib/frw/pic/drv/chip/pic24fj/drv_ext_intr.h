/* 
 * File:   drv_ext_intr.h
 * Author: dev
 *
 * Created on October 22, 2015, 5:14 PM
 */

#ifndef DRV_EXT_INTR_H
#define	DRV_EXT_INTR_H

#ifdef	__cplusplus
extern "C" {
#endif

#define DRV_EXT_INTR_IOCTL_MAP_PIN      0x01    // Map external interrupt pin, arg = &DRV_EXT_INTR_MAP_PIN
#define DRV_EXT_INTR_IOCTL_CFG          0x02    // arg = &DRV_EXT_INTR_CFG

/* set interrupt type
 * or interrupt return value
 * 
 */     
enum DRV_EXT_INTR_TYPE{
    DRV_EXT_INTR_NONE = 0,
    DRV_EXT_INTR_FALLING,
    DRV_EXT_INTR_RISING,
    DRV_EXT_INTR_BOTH
};
typedef struct{
    unsigned int rpin;      // RPINx pin
}DRV_EXT_INTR_MAP_PIN;
typedef struct{
    unsigned int intr_type;
}DRV_EXT_INTR_CFG;
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_EXT_INTR_H */

