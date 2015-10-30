#ifndef SYSTEM_H_
#define SYSTEM_H_
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <lib_debug.h>

#define Printf	LREP
#define CONSOLE_PrintHex(x)	LREP("%x", x)

#define SYS_CLK_FrequencySystemGet()    (25000000)

typedef union
{

    uint8_t  v[4];
    uint16_t w[2];
    uint32_t Val;

}API_UINT32_UNION;

typedef union
{

    uint8_t  v[2];
    uint16_t Val;

}API_UINT16_UNION;
#endif
