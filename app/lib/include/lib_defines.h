/*
 * lib_defines.h
 *
 *  Created on: Oct 11, 2015
 *      Author: dev
 */

#ifndef LIB_INCLUDE_LIB_DEFINES_H_
#define LIB_INCLUDE_LIB_DEFINES_H_

#if defined(__linux__)
#define DEBUG_BUFSIZE		(2048)
#define INT8        char
#define UINT8       unsigned char
#define INT16       short
#define UINT16      unsigned short
#define INT32       int
#define UINT32      unsigned int
#elif defined(__XC__)
#include <stdint.h>
#define INT8        int8_t
#define UINT8       uint8_t
#define INT16       int16_t
#define UINT16      uint16_t
#define INT32       int32_t
#define UINT32      uint32_t
#define DEBUG_BUFSIZE   32
#endif



#endif /* LIB_INCLUDE_LIB_DEFINES_H_ */
