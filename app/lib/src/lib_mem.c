/*
 * lib_mem.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <lib_mem.h>

extern void* frw_alloc(int length);
extern int   frw_free(void* mem, int length);

void* lib_alloc(int length){
	return frw_alloc(length);
}
int   lib_free(void* mem, int length){
	return frw_free(mem, length);
}



