/*
 * lib_debug.h
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */

#ifndef LIB_INCLUDE_LIB_DEBUG_H_
#define LIB_INCLUDE_LIB_DEBUG_H_
#ifdef __cplusplus
extern "C" {
#endif
#include "lib_defines.h"
typedef void (*DEBUG_CALLBACK)(const char* sz, void* obj);
void lib_debugPrint(const char* sz, ...);
void lib_debugDump(const void* mem, int length, const char* sz, ...);
void lib_debugSetCallback(DEBUG_CALLBACK fxn, void* obj);

#if defined(__linux__)
#define LREP	lib_debugPrint
#define DUMP	lib_debugDump
#define LREP_WARN(x, args...)	lib_debugPrint("warn:" x, ##args)
#define LREP_ERR(x, args...)	lib_debugPrint("err :" x, ##args)
#elif defined(__XC16__)
//extern void lib_debugPrintInt16(INT16 x);
//extern void lib_debugPrintUint16(UINT16 x);
//extern void lib_debugPrintHexa(UINT32 x);

#define LREP     lib_debugPrint
#define DUMP     lib_debugDump

//#define LREP_INT(x)        lib_debugPrintInt16(x)
//#define LREP_UINT(x)       lib_debugPrintUint16(x)
//#define LREP_HEX(x)        lib_debugPrintHexa(x) 
#endif
#ifdef __cplusplus
}
#endif
#endif /* LIB_INCLUDE_LIB_DEBUG_H_ */
