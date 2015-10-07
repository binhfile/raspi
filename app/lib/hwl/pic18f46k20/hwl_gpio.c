#include "hwl_gpio.h"

const unsigned char g_hwl_gpio_pin_analogable[] = {
    0/*RA0*/, 1/*RA1*/, 2/*RA2*/, 3/*RA3*/, 5/*RA5*/,
    4*8+0/*RE0*/, 4*8+1/*RAE1*/, 4*8+2/*RE2*/,
    8+2/*RB2*/, 8+3/*RB3*/, 8+1/*RB1*/, 8+4/*RB4*/, 8+0/*RB0*/
};
void HWL_GPIO_PIN_AS_DIGITAL(unsigned char pin){
    unsigned char index ;
    unsigned char *reg;
    for(index = 0; index < sizeof(g_hwl_gpio_pin_analogable); index++){
        if(g_hwl_gpio_pin_analogable[index] == pin){
            reg = (unsigned char*)(HWL_ANSEL + (index / 8));
            *reg = (((unsigned char)(*reg)) & (~(0x01 << (index % 8))));
            break;
        }
    }
}
void HWL_GPIO_PIN_DIRECTORY(unsigned char pin, unsigned char dir){
    unsigned char *reg = (unsigned char*)(HWL_TRIS + (pin / 8));
    if(dir) {
        // input
        *reg = (unsigned char)(*reg) | (unsigned char)(0x01 << (pin % 8));
    }else{
        // output
        *reg = (unsigned char)(*reg) & (unsigned char)(~(0x01 << (pin % 8)));
    }
}
void HWL_GPIO_PIN_WRITE(unsigned char pin, unsigned char val){
    if(val) {
        // input
        *((unsigned char*)(HWL_LAT + pin / 8)) = (unsigned char)(*((unsigned char*)(HWL_LAT + (pin / 8)))) | (unsigned char)(0x01 << (pin % 8));
    }else{
        // output
        *((unsigned char*)(HWL_LAT + pin / 8)) = (unsigned char)(*((unsigned char*)(HWL_LAT + (pin / 8)))) & (unsigned char)(~(0x01 << (pin % 8)));
    }
}
unsigned char HWL_GPIO_PIN_READ(unsigned char pin){
    return (((*((unsigned char*)(HWL_PORT + pin / 8))) >> (pin % 8)) & 0x01);
}
char HWL_GPIO_PULLUP(unsigned char pin, unsigned char set){
    unsigned char *reg = (unsigned char*)HWL_WPUB;
    if(pin >= 8 && pin <= 8 + 7){
        // RBx only
        if(set){
            *(reg) = ((*reg) | (((unsigned char)0x01) << (pin % 8)));
        }else{
            *(reg) = ((*reg) & (unsigned char)(~(0x01 << (pin % 8))));
        }
        reg = (unsigned char*)HWL_INTCON2;
        *(reg) = ((*reg) & (((unsigned char)0x01) << 7));
        return 0;
    }
    return -1;
}