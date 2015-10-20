/*
*********************************************************************************************************
*                                             Microchip dsPIC33FJ
*                                            Board Support Package
*
*                                                   Micrium
*                                    (c) Copyright 2005, Micrium, Weston, FL
*                                              All Rights Reserved
*
*
* File : BSP.C
* By   : Eric Shufro
*********************************************************************************************************
*/

#include <includes.h>
/*
*********************************************************************************************************
*                                              VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/
static  void  Tmr_TickInit(void);

/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    RCON    &= ~SWDTEN;                                                 /* Ensure Watchdog disabled via IDE CONFIG bits and SW.     */
#if defined (__dsPIC33F__) || defined(__dsPIC33E__)
    BSP_PLL_Init();                                                     /* Initialize the PLL                                       */
#endif
    Tmr_TickInit();                                                     /* Initialize the uC/OS-II tick interrupt                   */
}

/*
*********************************************************************************************************
*                                      BSP_PLL_Init()
*
* Description : This function configures and enables the PLL with the external oscillator
*               selected as the input clock to the PLL.
*
* Notes       : 1) The PLL output frequency is calculated by FIN * (M / (N1 * N2)).
*               2) FIN is the PLL input clock frequency, defined in bsp.h as
*                  CPU_PRIMARY_OSC_FR. This is the same as the external primary
*                  oscillator on the Explorer 16 Evaluation Board.
*               3) M is the desired PLL multiplier
*               4) N1 is the divider for FIN before FIN enters the PLL block (Pre-Divider)
*               5) N2 is the PLL output divider (Post-Divider)
*
* Summary     :    The PLL is configured as (8MHZ) * (40 / (2 * 2)) = 80MHZ
*                  The processor clock is (1/2) of the PLL output.
*                  Performance = 40 MIPS.
*********************************************************************************************************
*/
#if defined (__dsPIC33F__) || defined(__dsPIC33E__)
static  void  BSP_PLL_Init (void)
{
    PLLFBD   =     38;                                                  /* Set the Multiplier (M) to 40 (2 added automatically) 	*/
    CLKDIV   =      0;                                                  /* Clear the PLL Pre Divider bits, N1 = N2 = 2              */
}
#endif

/*
*********************************************************************************************************
*                                      BSP_CPU_ClkFrq()

* Description : This function determines the CPU clock frequency (Fcy)
* Returns     : The CPU frequency in (HZ)
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFrq (void)
{
    CPU_INT08U  Clk_Selected;
    CPU_INT16U  FRC_Div;
    CPU_INT32U  CPU_Clk_Frq;


#if defined (__dsPIC33E__) || defined (__dsPIC33F__)
    CPU_INT08U  PLL_n1;
    CPU_INT08U  PLL_n2;
    CPU_INT16U  PLL_m;
    PLL_m         =  (PLLFBD & PLLDIV_MASK) + 2;                        /* Get the Multiplier value                                 */
    PLL_n1        =  (CLKDIV & PLLPRE_MASK) + 2;                        /* Computer the Pre Divider value                           */
    PLL_n2        = ((CLKDIV & PLLPOST_MASK) >> 6);                     /* Get the Post Divider register value                      */
    PLL_n2        = ((PLL_n2 * 2) + 2);                                 /* Compute the Post Divider value */
#endif

    FRC_Div       = ((CLKDIV & FRCDIV_MASK) >> 8);                      /* Get the FRC Oscillator Divider register value            */
    FRC_Div       = ((1 << FRC_Div) * 2);                               /* Compute the FRC Divider value                            */

    Clk_Selected  =  (OSCCON & COSC_MASK) >> 12;                        /* Determine which clock source is currently selected       */

    switch (Clk_Selected) {
        case 0:                                                         /* Fast Oscillator (FRC) Selected                           */
             CPU_Clk_Frq   =   CPU_FRC_OSC_FRQ;                         /* Return the frequency of the internal fast oscillator     */
             break;

        case 1:   
             #if defined (__dsPIC33E__) || defined(__dsPIC33F__)
             CPU_Clk_Frq   = ((CPU_FRC_OSC_FRQ  * PLL_m) /              /* Compute the PLL output frequency using the FRC as FIN    */
                              (FRC_Div * PLL_n1 * PLL_n2));
             #else
             /* Fast Oscillator (FRC) with PLL Selected                  */
             CPU_Clk_Frq   =  (CPU_FRC_OSC_FRQ  * 4);                   /* Compute the PLL output frequency  = (FRC * 4)            */
             #endif
             break;

        case 2:                                                         /* Primary External Oscillator Selected                     */
             CPU_Clk_Frq   =   CPU_PRIMARY_OSC_FRQ;                     /* Return the frequency of the primary external oscillator  */
             break;

        case 3:       
             #if defined (__dsPIC33E__) || defined(__dsPIC33F__)
             CPU_Clk_Frq   = ((CPU_PRIMARY_OSC_FRQ * PLL_m) /           /* Compute the PLL output frq using the PRI EXT OSC as FIN  */
                              (PLL_n1 * PLL_n2));
             #else
                         /* Primary External Oscillator with PLL Selected            */
             CPU_Clk_Frq   =  (CPU_PRIMARY_OSC_FRQ * 4);                /* Compute the PLL output frq as (CPU_PRIMARY_OSC_FRQ * 4)  */
             #endif
             break;

        case 4:                                                         /* Secondary Oscillator Selected (SOCS)                     */
             CPU_Clk_Frq   =   CPU_SECONDARY_OSC_FRQ;                   /* Return the frq of the external secondary oscillator      */
             break;

        case 5:                                                         /* Low Power Oscillator (LPOSC) Selected                    */
             CPU_Clk_Frq   =   CPU_LOW_POWER_OSC_FRQ;                   /* Return the frq of the Low Power Oscillator               */
             break;

        case 6:
             CPU_Clk_Frq = 0;                                           /* Return 0 for the Reserved clock setting                  */
             break;

        case 7:                                                         /* Fast Oscillator (FRC) with FRCDIV Selected               */
             CPU_Clk_Frq   =   CPU_FRC_OSC_FRQ / FRC_Div;               /* Return the clock frequency of FRC / FRC_Div              */
             break;

        default:
             CPU_Clk_Frq = 0;                                           /* Return 0 if the clock source cannot be determined        */
             break;
    }

    CPU_Clk_Frq   /=  2;                                                /* Divide the final frq by 2, get the actual CPU Frq (Fcy)  */

    return (CPU_Clk_Frq);                                               /* Return the operating frequency                           */
}

/*
*********************************************************************************************************
*                                     DISABLE ALL INTERRUPTS
*
* Description : This function disables all interrupts from the interrupt controller.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_IntDisAll (void)
{
}
/*
*********************************************************************************************************
*                                   OSProbe_TmrInit()
*
* Description : This function is called to by uC/Probe Plug-In for uC/OS-II to initialize the
*               free running timer that is used to make time measurements.
*
* Arguments   : none
*
* Returns     : none
*
* Note(s)     : 1) This timer is shared with the uC/OS-II time tick and is initialized
*                  from Tmr_TickInit().
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN == 1)
void  OSProbe_TmrInit (void)
{
#if OS_PROBE_TIMER_SEL == 3
    T3CON  =   0;                                                       /* Use Internal Osc (Fosc / 4), 16 bit mode, prescaler = 1  */
    TMR3   =   0;                                                       /* Start counting from 0 and clear the prescaler count      */
    PR3    =   0xFFFF;                                                  /* Set the period register to its maximum value             */
    T3CON |=   TON;                                                     /* Start the timer                                          */
#endif

#if OS_PROBE_TIMER_SEL == 5
    T5CON  =   0;                                                       /* Use Internal Osc (Fosc / 4), 16 bit mode, prescaler = 1  */
    TMR5   =   0;                                                       /* Start counting from 0 and clear the prescaler count      */
    PR5    =   0xFFFF;                                                  /* Set the period register to its maximum value             */
    T5CON |=   TON;                                                     /* Start the timer                                          */
#endif
}
#endif

/*
*********************************************************************************************************
*                                   OSProbe_TmrRd()
*
* Description : This function is called to read the current counts of a 16 bit free running timer.
*
* Arguments   : none
*
* Returns     ; The 16 bit count (in a 32 bit variable) of the timer assuming the timer is an UP counter.
*********************************************************************************************************
*/

#if (uC_PROBE_OS_PLUGIN > 0) && (OS_PROBE_HOOKS_EN == 1)
CPU_INT32U  OSProbe_TmrRd (void)
{
#if OS_PROBE_TIMER_SEL == 3
    return ((CPU_INT32U)TMR3);                                          /* Return the value of timer 3 if selected                  */
#endif

#if OS_PROBE_TIMER_SEL == 5
    return ((CPU_INT32U)TMR5);                                          /* Return the value of timer 5 if selected                  */
#endif
}
#endif

/*
*********************************************************************************************************
*                                       TICKER INITIALIZATION
*
* Description : This function is called to initialize uC/OS-II's tick source (typically a timer generating
*               interrupts every 1 to 100 mS).
*
* Arguments   : none
*
* Note(s)     : 1) The timer operates at a frequency of Fosc / 4
*               2) The timer resets to 0 after period register match interrupt is generated
*********************************************************************************************************
*/

static  void  Tmr_TickInit (void)
{
    CPU_INT32U  tmr_frq;
    CPU_INT16U  cnts;


    tmr_frq   =   BSP_CPU_ClkFrq();                                     /* Get the CPU Clock Frequency (Hz) (Fcy)                   */
    cnts      =   (tmr_frq / OS_TICKS_PER_SEC) - 1;                     /* Calaculate the number of timer ticks between interrupts  */

#if BSP_OS_TMR_SEL == 2
    T2CON     =   0;                                                    /* Use Internal Osc (Fcy), 16 bit mode, prescaler = 1  		*/
    TMR2      =   0;                                                    /* Start counting from 0 and clear the prescaler count      */
    PR2       =   cnts;                                                 /* Set the period register                                  */
    IPC1     &=  ~T2IP_MASK;                                            /* Clear all timer 2 interrupt priority bits                */
    IPC1     |=  (TIMER_INT_PRIO << 12);                                /* Set timer 2 to operate with an interrupt priority of 4   */
    IFS0     &=  ~T2IF;                                                 /* Clear the interrupt for timer 2                          */
    IEC0     |=   T2IE;                                                 /* Enable interrupts for timer 2                            */
    T2CON    |=   TON;                                                  /* Start the timer                                          */
#endif

#if BSP_OS_TMR_SEL == 4
    T4CON     =   0;                                                    /* Use Internal Osc (Fcy), 16 bit mode, prescaler = 1  		*/
    TMR4      =   0;                                                    /* Start counting from 0 and clear the prescaler count      */
    PR4       =   cnts;                                                 /* Set the period register                                  */
    IPC6     &=  ~T4IP_MASK;                                            /* Clear all timer 4 interrupt priority bits                */
    IPC6     |=  (TIMER_INT_PRIO << 12);                                /* Set timer 4 to operate with an interrupt priority of 4   */
    IFS1     &=  ~T4IF;                                                 /* Clear the interrupt for timer 4                          */
    IEC1     |=   T4IE;                                                 /* Enable interrupts for timer 4                            */
    T4CON    |=   TON;                                                  /* Start the timer                                          */
#endif
}

/*
*********************************************************************************************************
*                                     OS TICK INTERRUPT SERVICE ROUTINE
*
* Description : This function handles the timer interrupt that is used to generate TICKs for uC/OS-II.
*********************************************************************************************************
*/

void OS_Tick_ISR_Handler (void)
{
#if  BSP_OS_TMR_SEL == 2
    IFS0 &= ~T2IF;
#endif

#if  BSP_OS_TMR_SEL == 4
    IFS1 &= ~T41F;
#endif

    OSTimeTick();
}

