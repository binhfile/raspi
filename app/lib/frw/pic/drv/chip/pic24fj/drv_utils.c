#include "drv_utils.h"
#include "drv_common.h"
#include <xc.h>
UINT32  drv_getCpuClockFreq (void)
{
    UINT8   Clk_Selected;
    UINT16  FRC_Div;
    UINT32  CPU_Clk_Frq;


#if defined (__dsPIC33E__) || defined (__dsPIC33F__)
    UINT8  PLL_n1;
    UINT8  PLL_n2;
    UINT16  PLL_m;
    PLL_m         =  (PLLFBD & PLLDIV_MASK) + 2;                        /* Get the Multiplier value                                 */
    PLL_n1        =  (CLKDIV & PLLPRE_MASK) + 2;                        /* Computer the Pre Divider value                           */
    PLL_n2        = ((CLKDIV & PLLPOST_MASK) >> 6);                     /* Get the Post Divider register value                      */
    PLL_n2        = ((PLL_n2 * 2) + 2);                                 /* Compute the Post Divider value */
#endif

    FRC_Div       = ((CLKDIV & DRV_FRCDIV_MASK) >> 8);                      /* Get the FRC Oscillator Divider register value            */
    FRC_Div       = ((1 << FRC_Div) * 2);                               /* Compute the FRC Divider value                            */

    Clk_Selected  =  (OSCCON & DRV_COSC_MASK) >> 12;                        /* Determine which clock source is currently selected       */

    switch (Clk_Selected) {
        case 0:                                                         /* Fast Oscillator (FRC) Selected                           */
             CPU_Clk_Frq   =   drv_commonGetFRCFreq();                         /* Return the frequency of the internal fast oscillator     */
             break;

        case 1:   
             #if defined (__dsPIC33E__) || defined(__dsPIC33F__)
             CPU_Clk_Frq   = ((DRV_FRC_FREQ  * PLL_m) /              /* Compute the PLL output frequency using the FRC as FIN    */
                              (FRC_Div * PLL_n1 * PLL_n2));
             #else
             /* Fast Oscillator (FRC) with PLL Selected                  */
             CPU_Clk_Frq   =  (drv_commonGetFRCFreq()  * 4);                   /* Compute the PLL output frequency  = (FRC * 4)            */
             #endif
             break;

        case 2:                                                         /* Primary External Oscillator Selected                     */
             CPU_Clk_Frq   =   drv_commonGetPrimaryFreq();                     /* Return the frequency of the primary external oscillator  */
             break;

        case 3:       
             #if defined (__dsPIC33E__) || defined(__dsPIC33F__)
             CPU_Clk_Frq   = ((DRV_PRIMARY_FREQ * PLL_m) /           /* Compute the PLL output frq using the PRI EXT OSC as FIN  */
                              (PLL_n1 * PLL_n2));
             #else
                         /* Primary External Oscillator with PLL Selected            */
             CPU_Clk_Frq   =  (drv_commonGetPrimaryFreq() * 4);                /* Compute the PLL output frq as (DRV_PRIMARY_FREQ * 4)  */
             #endif
             break;

        case 4:                                                         /* Secondary Oscillator Selected (SOCS)                     */
             CPU_Clk_Frq   =   drv_commonGetSecondaryFreq();                   /* Return the frq of the external secondary oscillator      */
             break;

        case 5:                                                         /* Low Power Oscillator (LPOSC) Selected                    */
             CPU_Clk_Frq   =   drv_commonGetLowpowerFreq();                   /* Return the frq of the Low Power Oscillator               */
             break;

        case 6:
             CPU_Clk_Frq = 0;                                           /* Return 0 for the Reserved clock setting                  */
             break;

        case 7:                                                         /* Fast Oscillator (FRC) with FRCDIV Selected               */
             CPU_Clk_Frq   =   drv_commonGetFRCFreq() / FRC_Div;               /* Return the clock frequency of FRC / FRC_Div              */
             break;

        default:
             CPU_Clk_Frq = 0;                                           /* Return 0 if the clock source cannot be determined        */
             break;
    }

    CPU_Clk_Frq   /=  2;                                                /* Divide the final frq by 2, get the actual CPU Frq (Fcy)  */

    return (CPU_Clk_Frq);                                               /* Return the operating frequency                           */
}
