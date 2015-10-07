/* 
 * File:   main.c
 * Author: dev
 *
 * Created on October 7, 2015, 9:30 AM
 */
#include <xc.h>
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1H
#pragma config FOSC     = HS        // Oscillator Selection bits (11XX External RC oscillator, CLKOUT function on RA6)
#pragma config FCMEN    = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO     = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT     = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN    = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV     = 18        // Brown Out Reset Voltage bits (VBOR set to 1.8 V nominal)

// CONFIG2H
#pragma config WDTEN    = OFF      // Watchdog Timer Enable bit (WDT is controlled by SWDTEN bit of the WDTCON register)
#pragma config WDTPS    = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX   = PORTC   // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN   = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC  = OFF    // Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config HFOFST   = ON      // HFINTOSC Fast Start-up (HFINTOSC starts clocking the CPU without waiting for the oscillator to stablize.)
#pragma config MCLRE    = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN   = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP      = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST    = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0      = OFF        // Code Protection Block 0 (Block 0 (000800-003FFFh) not code-protected)
#pragma config CP1      = OFF        // Code Protection Block 1 (Block 1 (004000-007FFFh) not code-protected)
#pragma config CP2      = OFF        // Code Protection Block 2 (Block 2 (008000-00BFFFh) not code-protected)
#pragma config CP3      = OFF        // Code Protection Block 3 (Block 3 (00C000-00FFFFh) not code-protected)

// CONFIG5H
#pragma config CPB      = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
#pragma config CPD      = OFF        // Data EEPROM Code Protection bit (Data EEPROM not code-protected)

// CONFIG6L
#pragma config WRT0     = OFF       // Write Protection Block 0 (Block 0 (000800-003FFFh) not write-protected)
#pragma config WRT1     = OFF       // Write Protection Block 1 (Block 1 (004000-007FFFh) not write-protected)
#pragma config WRT2     = OFF       // Write Protection Block 2 (Block 2 (008000-00BFFFh) not write-protected)
#pragma config WRT3     = OFF       // Write Protection Block 3 (Block 3 (00C000h-00FFFFh) not write-protected)

// CONFIG6H
#pragma config WRTC     = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
#pragma config WRTB     = OFF       // Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
#pragma config WRTD     = OFF       // Data EEPROM Write Protection bit (Data EEPROM not write-protected)

// CONFIG7L
#pragma config EBTR0    = OFF      // Table Read Protection Block 0 (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR1    = OFF      // Table Read Protection Block 1 (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
#pragma config EBTR2    = OFF      // Table Read Protection Block 2 (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
#pragma config EBTR3    = OFF      // Table Read Protection Block 3 (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB    = OFF      // Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

#define         MEM_TANK_SIZE       (2048)
unsigned char   g_memTank[MEM_TANK_SIZE];
unsigned int    g_memTankSize = MEM_TANK_SIZE;
#include <lib_gpio.h>
void UserTask (void *pdata)
{
//    int i, j;
    while(1){
//        lib_gpioWrite(pdata, 0);
//        for(i = 0; i < 1000; i++){
//            for(j = 0; j  <50; j++){
//                asm("nop");
//            }
//        }
//        lib_gpioWrite(pdata, 1);
//        for(i = 0; i < 1000; i++){
//            for(j = 0; j  <50; j++){
//                asm("nop");
//            }
//        }
    }
}
int main(int argc, char** argv) {
    void* gpioRB0 = 0;
    void* gpioRB1 = 0;
    void* gpioRB2 = 0;
    unsigned char val;

    TRISB = 0xff;

    gpioRB0 = lib_gpioAllocDevice(1*8+0);
    gpioRB1 = lib_gpioAllocDevice(1*8+1);
    gpioRB2 = lib_gpioAllocDevice(1*8+2);
    lib_gpioSetDirectory(gpioRB0, 0);
    lib_gpioSetDirectory(gpioRB1, 0);
    lib_gpioSetDirectory(gpioRB2, 1);
//    UserTask(gpioRB0);

    while(1){
        val = lib_gpioRead(gpioRB2);
        lib_gpioWrite(gpioRB1, val);
    }

    return (0);
}

