#include "unistd.h"
#include <ucos_ii.h>

unsigned int sleep (unsigned int __seconds){
    int hour, min;
    
    hour = __seconds / (60 * 60);
    __seconds = __seconds - hour * (60 * 60);
    min = __seconds / 60;
    __seconds = __seconds - min * 60;
    OSTimeDlyHMSM(hour, min, __seconds, 0);
    return 0;
}
int msleep (unsigned int ms){
    int sec = ms / 1000;
    ms = ms - sec * 1000;
    OSTimeDlyHMSM(0,0, sec, ms);
    return 0;
}
