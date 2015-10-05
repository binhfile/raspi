/*
 * frw_mem.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <stdlib.h>

inline void* frw_alloc(int length){
	return malloc(length);
}
inline int   frw_free(void* mem){
	if(mem){
		free(mem);
		return 0;
	}
	else return -1;
}


