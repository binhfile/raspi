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
typedef void (*DEBUG_CALLBACK)(const char* sz, void* obj);
void lib_debugPrint(const char* sz, ...);
void lib_debugDump(const void* mem, int length, const char* sz, ...);
void lib_debugSetCallback(DEBUG_CALLBACK fxn, void* obj);
#define LREP	lib_debugPrint
#define DUMP	lib_debugDump

#define LREP_WARN(x, args...)	lib_debugPrint("warn:" x, ##args)
#define LREP_ERR(x, args...)	lib_debugPrint("err :" x, ##args)
#define DEBUG_BUFSIZE		2048
#ifdef __cplusplus
}
#endif
#endif /* LIB_INCLUDE_LIB_DEBUG_H_ */
