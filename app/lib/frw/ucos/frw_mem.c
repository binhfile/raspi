/*
 * frw_mem.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <stdlib.h>
/* config @ app */
extern unsigned char g_memTank[];
extern unsigned int  g_memTankSize;

unsigned int g_memUsedLength = 0;
void* frw_alloc(int length){
    void* mem = 0;
    if(length < 0) length = 0;
    if(g_memUsedLength + length <= g_memTankSize){
        mem = &g_memTank[g_memUsedLength];
        g_memUsedLength = g_memUsedLength + length;
    }
    return mem;
}
int   frw_free(void* mem, int length){
    if(mem){
        return 0;
    }
    else return -1;
}


