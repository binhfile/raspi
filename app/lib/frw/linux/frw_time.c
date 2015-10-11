/*
 * frw_time.c
 *
 *  Created on: Oct 11, 2015
 *      Author: dev
 */

#include <sys/timeb.h>

unsigned int frw_timeGetCurrentMs(){
	unsigned int ret = 0;
    struct timeb tv;
    ftime(&tv);
    ret = (unsigned int)(tv.time * 1000 + tv.millitm);
    return ret;
}
