/* 
 * File:   drv_perimap.h
 * Author: dev
 *
 * Created on October 20, 2015, 5:00 PM
 */

#ifndef DRV_PERIMAP_H
#define	DRV_PERIMAP_H

#ifdef	__cplusplus
extern "C" {
#endif
#include "drv_regs.h"
    
    enum DRV_PERIMAP_INPUT{
        DRV_PERIMAP_INPUT_UNUSED0 = 0,  // RPINR0
        DRV_PERIMAP_INPUT_INT1,        
        DRV_PERIMAP_INPUT_INT2,         // RPINR1
        DRV_PERIMAP_INPUT_INT3,
        DRV_PERIMAP_INPUT_INT4,         // RPINR2
        DRV_PERIMAP_INPUT_UNUSED1,
        DRV_PERIMAP_INPUT_T2CK,         // RPINR3
        DRV_PERIMAP_INPUT_T3CK,
        DRV_PERIMAP_INPUT_T4CK,         // RPINR4
        DRV_PERIMAP_INPUT_T5CK,
        DRV_PERIMAP_INPUT_UNUSED2,      // RPINR5
        DRV_PERIMAP_INPUT_UNUSED3,
        DRV_PERIMAP_INPUT_UNUSED4,      // RPINR6
        DRV_PERIMAP_INPUT_UNUSED5,        
        DRV_PERIMAP_INPUT_IC1,          // RPINR7
        DRV_PERIMAP_INPUT_IC2,
        DRV_PERIMAP_INPUT_IC3,          // RPINR8
        DRV_PERIMAP_INPUT_IC4,
        DRV_PERIMAP_INPUT_IC5,          // RPINR9
        DRV_PERIMAP_INPUT_IC6,
        DRV_PERIMAP_INPUT_IC7,          // RPINR10
        DRV_PERIMAP_INPUT_IC8,
        DRV_PERIMAP_INPUT_OCFA,         // RPINR11
        DRV_PERIMAP_INPUT_OCFB,
        DRV_PERIMAP_INPUT_UNUSED6,      // RPINR12
        DRV_PERIMAP_INPUT_UNUSED7,
        DRV_PERIMAP_INPUT_UNUSED8,      // RPINR13
        DRV_PERIMAP_INPUT_UNUSED9,   
        DRV_PERIMAP_INPUT_UNUSED10,      // RPINR14
        DRV_PERIMAP_INPUT_UNUSED11,    
        DRV_PERIMAP_INPUT_UNUSED12,      // RPINR15
        DRV_PERIMAP_INPUT_IC9,
        DRV_PERIMAP_INPUT_UNUSED13,       // RPINR16
        DRV_PERIMAP_INPUT_UNUSED14,      
        DRV_PERIMAP_INPUT_UNUSED15,      // RPINR17
        DRV_PERIMAP_INPUT_U3RX,
        DRV_PERIMAP_INPUT_U1RX,          // RPINR18
        DRV_PERIMAP_INPUT_U1CTS,
        DRV_PERIMAP_INPUT_U2RX,          // RPINR19  
        DRV_PERIMAP_INPUT_U2CTS,
        DRV_PERIMAP_INPUT_SDI1,          // RPINR20  
        DRV_PERIMAP_INPUT_SCK1IN,
        DRV_PERIMAP_INPUT_SS1IN,         // RPINR21
        DRV_PERIMAP_INPUT_U3CTS,
        DRV_PERIMAP_INPUT_SDI2,          // RPINR22     
        DRV_PERIMAP_INPUT_SCK2IN,
        DRV_PERIMAP_INPUT_SS2IN,         // RPINR23
        DRV_PERIMAP_INPUT_UNUSED16,
        DRV_PERIMAP_INPUT_UNUSED17,       // RPINR24 
        DRV_PERIMAP_INPUT_UNUSED18,
        DRV_PERIMAP_INPUT_UNUSED19,       // RPINR25
        DRV_PERIMAP_INPUT_UNUSED20,
        DRV_PERIMAP_INPUT_UNUSED21,       // RPINR26
        DRV_PERIMAP_INPUT_UNUSED22,
        DRV_PERIMAP_INPUT_U4RX,          // RPINR27
        DRV_PERIMAP_INPUT_U4CTS,
        DRV_PERIMAP_INPUT_SDI3,          // RPINR28
        DRV_PERIMAP_INPUT_SCK3IN,
        DRV_PERIMAP_INPUT_SS3IN,         // RPINR29
    };
    enum DRV_PERIMAP_OUTPUT{
        DRV_PERIMAP_OUTPUT_NULL     = 0,
        DRV_PERIMAP_OUTPUT_C1OUT    = 1,
        DRV_PERIMAP_OUTPUT_C2OUT    = 2,
        DRV_PERIMAP_OUTPUT_U1TX     = 3,
        DRV_PERIMAP_OUTPUT_U1RTS    = 4,
        DRV_PERIMAP_OUTPUT_U2TX     = 5,
        DRV_PERIMAP_OUTPUT_U2RTS    = 6,
        DRV_PERIMAP_OUTPUT_SDO1     = 7,
        DRV_PERIMAP_OUTPUT_SCK1OUT  = 8,
        DRV_PERIMAP_OUTPUT_SS1OUT   = 9,
        DRV_PERIMAP_OUTPUT_SDO2     = 10,
        DRV_PERIMAP_OUTPUT_SCK2OUT  = 11,
        DRV_PERIMAP_OUTPUT_SS2OUT   = 12 ,
        DRV_PERIMAP_OUTPUT_OC1      = 18,
        DRV_PERIMAP_OUTPUT_OC2      = 19,
        DRV_PERIMAP_OUTPUT_OC3      = 20,
        DRV_PERIMAP_OUTPUT_OC4      = 21,
        DRV_PERIMAP_OUTPUT_OC5      = 22,
        DRV_PERIMAP_OUTPUT_OC6      = 23,
        DRV_PERIMAP_OUTPUT_OC7      = 24,
        DRV_PERIMAP_OUTPUT_OC8      = 25,
        DRV_PERIMAP_OUTPUT_U3TX     = 28,
        DRV_PERIMAP_OUTPUT_U3RTS    = 29,
        DRV_PERIMAP_OUTPUT_U4TX     = 30,
        DRV_PERIMAP_OUTPUT_U4RTS    = 31,
        DRV_PERIMAP_OUTPUT_SDO3     = 32,
        DRV_PERIMAP_OUTPUT_SCK3OUT  = 33,
        DRV_PERIMAP_OUTPUT_SS3OUT   = 34,
        DRV_PERIMAP_OUTPUT_OC9      = 35,
        DRV_PERIMAP_OUTPUT_C3OUT    = 36,
    };
#define DRV_PERI_INPUT_MAP(peri_sel, pin_sel) { \
        REG((RPIN_REG_BASE_ADDRESS + (((unsigned int)peri_sel >> 1) <<  1))) = \
            (REG((RPIN_REG_BASE_ADDRESS + (((unsigned int)peri_sel >> 1) <<  1))) & \
            (((unsigned int)0x3F << ((peri_sel & 0x01) ? 8 : 0)))) | \
            ((unsigned int)pin_sel << ((peri_sel & 0x01) ? 8 : 0)); \
    }
#define DRV_PERI_OUTPUT_MAP(peri_sel, pin_sel){\
        REG((RPO_REG_BASE_ADDRESS + (((unsigned int)pin_sel >> 1) << 1))) = \
            (REG((RPO_REG_BASE_ADDRESS + (((unsigned int)pin_sel >> 1) << 1))) & \
            (((unsigned int)0x3F << ((pin_sel & 0x01) ? 8 : 0)))) | \
            ((unsigned int)peri_sel << ((pin_sel & 0x01) ? 8 : 0)); \
    }
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PERIMAP_H */

