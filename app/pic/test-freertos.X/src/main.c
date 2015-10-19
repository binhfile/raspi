/* Scheduler include files. */
#define USE_AND_MASKS
#include "FreeRTOS.h"
#include "task.h"
#include <usart.h> 
#include "cfg.h"
// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = SBORDIS  // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 18        // Brown Out Reset Voltage bits (VBOR set to 1.8 V nominal)

// CONFIG2H
#pragma config WDTEN = OFF      // Watchdog Timer Enable bit (WDT is controlled by SWDTEN bit of the WDTCON register)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config HFOFST = ON      // HFINTOSC Fast Start-up (HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1 = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2 = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3 = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1 = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2 = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3 = OFF       // Write Protection Block 3 (Block 3 (00C000h-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

/* Priority definitions for some of the tasks.  Other tasks just use the idle
priority. */
#define mainQUEUE_POLL_PRIORITY			( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY			( tskIDLE_PRIORITY + 3 )

/* Constants required for the communications.  Only one character is ever
transmitted. */
#define mainCOMMS_QUEUE_LENGTH			( 5 )
#define mainNO_BLOCK					( ( TickType_t ) 0 )
#define mainBAUD_RATE					( ( unsigned long ) 9600 )

#include <lib_debug.h>

/*
 * The task function for the "Check" task.
 */
static void vTask1( void *pvParameters );
static void vTask2( void *pvParameters );

/*
 * Checks the unique counts of other tasks to ensure they are still operational.
 * Returns pdTRUE if an error is detected, otherwise pdFALSE.
 */
//static portBASE_TYPE prvCheckOtherTasksAreStillRunning( void );

/*-----------------------------------------------------------*/

/* Creates the tasks, then starts the scheduler. */
void main( void )
{     
    OSCTUNEbits.PLLEN = 0;
    ANSELH = 0x00;
    ANSEL = 0x00;
    TXSTA       = 0x24;
    RCSTA       = 0x90;
    BAUDCON     = 0x00;
    SPBRG       = 0x0D;
    
	vPortInitialiseBlocks();
//    xSerialPortInitMinimal(9600, 5);

	/* Start the check task defined in this file. */
	xTaskCreate( vTask1, "Task 1", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );
    xTaskCreate( vTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY+1, NULL );

	/* Start the scheduler.  Will never return here. */
	vTaskStartScheduler();
//    vTask2(0);
}
/*-----------------------------------------------------------*/
static void vTask1( void *pvParameters )
{
	/* Cycle for ever, delaying then checking all the other tasks are still
	operating without error. */
    int i, j;
    TRISB = 0;
    LATB = 0;
	for( ;; )
	{
        LATB = LATB & (~0x01);
        for(i = 0 ;  i < 1000; i++){
            for(j = 0; j < 100; j++){
#if defined(__XC8__)
                asm("nop");
#else
                _asm
                        NOP
                _endasm
#endif
            }
        }
        LATB = LATB | (0x01);
        for(i = 0 ;  i < 1000; i++){
            for(j = 0; j < 100; j++){
#if defined(__XC8__)
                asm("nop");
#else
                _asm
                        NOP
                _endasm
#endif
            }
        }
	}
}

static void vTask2( void *pvParameters )
{
	/* Cycle for ever, delaying then checking all the other tasks are still
	operating without error. */
    int i, j;
             int len;
   
    ANSELH = 0x00;
    TRISB = 0;
    LATB = 0;
    len = 7;
    
	for( ;; )
	{
        LREP("Trigger %d\r\n", 1);
        LATB = LATB & (~(0x01 << 1));
        for(i = 0 ;  i < 1000; i++){
            for(j = 0; j < 50; j++){
#if defined(__XC8__)
                asm("nop");
#else
                _asm
                        NOP
                _endasm
#endif
            }
        }
        LATB = LATB | (0x01 << 1);
        for(i = 0 ;  i < 1000; i++){
            for(j = 0; j < 50; j++){
#if defined(__XC8__)
                asm("nop");
#else
                _asm
                        NOP
                _endasm
#endif
            }
        }
	}
}
/*-----------------------------------------------------------*/
void printHexa(unsigned char x){
    x = x & 0x0F;
    if(x >= 0 && x <= 9) x = x + '0';
    else if (x >= 10 && x <= 15) x = x - 10 + 'A';
    else x = '?';
    TXREG = x;
    while(!TXSTAbits.TRMT){ Nop();}
}
void frw_debugPrint(char sz[]){
//    int i;
//    for(i = 0; i < 64; i++){
//        if(p[i] == '\0') break;
//        TXREG = p[i];
//        while(!TXSTAbits.TRMT){ Nop();}
//    }
    
//    unsigned int addr = (unsigned int)sz;
//    printHexa(addr >> 12);
//    printHexa(addr >> 8);
//    printHexa(addr >> 4);
//    printHexa(addr >> 0);
//    addr = (unsigned int)&g_debugBuffer[0];
//    TXREG = '-';
//    while(!TXSTAbits.TRMT){ Nop();}
//    printHexa(addr >> 12);
//    printHexa(addr >> 8);
//    printHexa(addr >> 4);
//    printHexa(addr >> 0);
    
    TXREG = sz[0];
    while(!TXSTAbits.TRMT){ Nop();}
    TXREG = sz[1];
    while(!TXSTAbits.TRMT){ Nop();}
    
    TXREG = '\r';
    while(!TXSTAbits.TRMT){ Nop();}
    TXREG = '\n';
    while(!TXSTAbits.TRMT){ Nop();}
    
    
}

// end of file
