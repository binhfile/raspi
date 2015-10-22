/* 
 * File:   drv_gpio.h
 * Author: dev
 *
 * Created on October 22, 2015, 11:39 AM
 */

#ifndef DRV_GPIO_H
#define	DRV_GPIO_H

#ifdef	__cplusplus
extern "C" {
#endif
/*port =  A, B, C, D, E, F, G*/
enum DRV_GPIO_PIN{
    // PORT A
    DRV_GPIO_RA0 = 0,
    DRV_GPIO_RA1,
    DRV_GPIO_RA2,
    DRV_GPIO_RA3,
    DRV_GPIO_RA4,
    DRV_GPIO_RA5,
    DRV_GPIO_RA6,
    DRV_GPIO_RA7,
    DRV_GPIO_RA8,
    DRV_GPIO_RA9,
    DRV_GPIO_RA10,
    DRV_GPIO_RA11,
    DRV_GPIO_RA12,
    DRV_GPIO_RA13,
    DRV_GPIO_RA14,
    DRV_GPIO_RA15, 
    // PORT B
    DRV_GPIO_RB0,
    DRV_GPIO_RB1,
    DRV_GPIO_RB2,
    DRV_GPIO_RB3,
    DRV_GPIO_RB4,
    DRV_GPIO_RB5,
    DRV_GPIO_RB6,
    DRV_GPIO_RB7,
    DRV_GPIO_RB8,
    DRV_GPIO_RB9,
    DRV_GPIO_RB10,
    DRV_GPIO_RB11,
    DRV_GPIO_RB12,
    DRV_GPIO_RB13,
    DRV_GPIO_RB14,
    DRV_GPIO_RB15, 
    // PORT C
    DRV_GPIO_RC0,
    DRV_GPIO_RC1,
    DRV_GPIO_RC2,
    DRV_GPIO_RC3,
    DRV_GPIO_RC4,
    DRV_GPIO_RC5,
    DRV_GPIO_RC6,
    DRV_GPIO_RC7,
    DRV_GPIO_RC8,
    DRV_GPIO_RC9,
    DRV_GPIO_RC10,
    DRV_GPIO_RC11,
    DRV_GPIO_RC12,
    DRV_GPIO_RC13,
    DRV_GPIO_RC14,
    DRV_GPIO_RC15, 
    // PORT D
    DRV_GPIO_RD0,
    DRV_GPIO_RD1,
    DRV_GPIO_RD2,
    DRV_GPIO_RD3,
    DRV_GPIO_RD4,
    DRV_GPIO_RD5,
    DRV_GPIO_RD6,
    DRV_GPIO_RD7,
    DRV_GPIO_RD8,
    DRV_GPIO_RD9,
    DRV_GPIO_RD10,
    DRV_GPIO_RD11,
    DRV_GPIO_RD12,
    DRV_GPIO_RD13,
    DRV_GPIO_RD14,
    DRV_GPIO_RD15, 
    // PORT E
    DRV_GPIO_RE0,
    DRV_GPIO_RE1,
    DRV_GPIO_RE2,
    DRV_GPIO_RE3,
    DRV_GPIO_RE4,
    DRV_GPIO_RE5,
    DRV_GPIO_RE6,
    DRV_GPIO_RE7,
    DRV_GPIO_RE8,
    DRV_GPIO_RE9,
    DRV_GPIO_RE10,
    DRV_GPIO_RE11,
    DRV_GPIO_RE12,
    DRV_GPIO_RE13,
    DRV_GPIO_RE14,
    DRV_GPIO_RE15, 
    // PORT F
    DRV_GPIO_RF0,
    DRV_GPIO_RF1,
    DRV_GPIO_RF2,
    DRV_GPIO_RF3,
    DRV_GPIO_RF4,
    DRV_GPIO_RF5,
    DRV_GPIO_RF6,
    DRV_GPIO_RF7,
    DRV_GPIO_RF8,
    DRV_GPIO_RF9,
    DRV_GPIO_RF10,
    DRV_GPIO_RF11,
    DRV_GPIO_RF12,
    DRV_GPIO_RF13,
    DRV_GPIO_RF14,
    DRV_GPIO_RF15,     
   // PORT G
    DRV_GPIO_RG0,
    DRV_GPIO_RG1,
    DRV_GPIO_RG2,
    DRV_GPIO_RG3,
    DRV_GPIO_RG4,
    DRV_GPIO_RG5,
    DRV_GPIO_RG6,
    DRV_GPIO_RG7,
    DRV_GPIO_RG8,
    DRV_GPIO_RG9,
    DRV_GPIO_RG10,
    DRV_GPIO_RG11,
    DRV_GPIO_RG12,
    DRV_GPIO_RG13,
    DRV_GPIO_RG14,
    DRV_GPIO_RG15,     
};
enum DRV_GPIO_DIR{
    DRV_GPIO_OUTPUT = 0,
    DRV_GPIO_INPUT
};
enum DRV_GPIO_OPEN_DRAIN{
    DRV_GPIO_OPEN_DRAIN_DISABLE = 0,
    DRV_GPIO_OPEN_DRAIN_ENABLE
};
enum DRV_GPIO_VALUE{
    DRV_GPIO_LOW = 0,
    DRV_GPIO_HIGH
};
#define DRV_GPIO_IOCTL_ENABLE       0x01 // enable gpio pin, arg = &DRV_GPIO_ENABLE
#define DRV_GPIO_IOCTL_WRITE        0x02 // write gpio pin value, arg = &DRV_GPIO_WRITE
#define DRV_GPIO_IOCTL_READ         0x03 // read gpio pin value, arg = &DRV_GPIO_READ
#define DRV_GPIO_IOCTL_SET_ICN      0x04 // Set input change notitication arg = &DRV_GPIO_INPUT_CHANGE_NOTIFICATION

typedef struct{
    unsigned int pin;    // Pin id = Port_offset * 16 + pin_offset, use R(A/B/C/D/E/F/G)x pin
    unsigned int dir;    // Direction, 0-output, 1-input
    unsigned int opendrain;  // 1- set output open drain
}DRV_GPIO_ENABLE;
typedef struct{
    unsigned int pin;   // Pin id = Port_offset * 16 + pin_offset, use R(A/B/C/D/E/F/G)x pin
    unsigned int value;
}DRV_GPIO_WRITE;
typedef struct{
    unsigned int pin;   // Pin id = Port_offset * 16 + pin_offset, use R(A/B/C/D/E/F/G)x pin
    unsigned int value;
}DRV_GPIO_READ;
typedef struct{
    unsigned int cn_pin;    // use CNx pin
    unsigned int enable;    // 0-disable
    unsigned int pull_up;   // 0-disable
    unsigned int pull_down; // 0-disable
}DRV_GPIO_INPUT_CHANGE_NOTIFICATION;
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_GPIO_H */

