/*
 * lib_debug.c
 *
 *  Created on: Oct 5, 2015
 *      Author: dev
 */
#include <lib_debug.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
DEBUG_CALLBACK	g_debug_callback_fxn = 0;
void*			g_debug_callback_obj = 0;
extern void frw_debugPrint(const void* sz);
void lib_debugSetCallback(DEBUG_CALLBACK fxn, void* obj){
	g_debug_callback_fxn = fxn;
	g_debug_callback_obj = obj;
}
void lib_debugPrint(const char* sz, ...){
    char szBuffer[DEBUG_BUFSIZE];
    va_list arglist;
    va_start(arglist, sz);
    vsnprintf(szBuffer, DEBUG_BUFSIZE - 1, sz, arglist);
    if(g_debug_callback_fxn)
    	g_debug_callback_fxn(szBuffer, g_debug_callback_obj);
    else
    {
    	frw_debugPrint(szBuffer);
    }
}
void lib_debugDump(const void* mem, int length, const char* sz, ...){
    unsigned char* p = (unsigned char*)mem;
    char szBuffer[DEBUG_BUFSIZE];
    int iLen, i;
    va_list arglist;

    va_start(arglist, sz);
    vsnprintf(szBuffer, DEBUG_BUFSIZE - 1, sz, arglist);
    if(g_debug_callback_fxn)
    	g_debug_callback_fxn(szBuffer, g_debug_callback_obj);
    else
    {
    	frw_debugPrint(szBuffer);
    }
    lib_debugPrint("\n");
    while (length > 0)
    {
        iLen = (length > 16) ? 16 : length;
        for(i = 0; i < 16; i++) szBuffer[i] = 0;
        for(i = 0; i < iLen; i++) szBuffer[i] = p[i];
        for (i = 0; i < 16; i++)
        {
            if (i < iLen)
            	lib_debugPrint("%02X ", szBuffer[i]);
            else
            	lib_debugPrint("   ");
        }
        lib_debugPrint("\t");
        for (i = 0; i < 16; i++)
        {
            if (i < iLen)
            {
                if (isprint(szBuffer[i]))
                	lib_debugPrint("%c", (char)szBuffer[i]);
                else
                	lib_debugPrint(".");
            }
            else
            	lib_debugPrint(" ");
        }
        lib_debugPrint("\n");
        length -= iLen;
        p += iLen;
    }
}



