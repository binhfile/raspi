/*
 * frw_debug_stdout.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <stdio.h>
#include <string.h>
void frw_debugPrint(const void* sz){
	fwrite(sz, 1, strlen(sz), stdout);
	fflush(stdout);
}


