/* 
 * File:   app_cfg.h
 * Author: dev
 *
 * Created on October 19, 2015, 11:20 AM
 */

#ifndef PRJ_CFG_H
#define	PRJ_CFG_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <frw_string.h>
    
#define FREQ_OSC    (8000000L)
#define FREQ_DIV    (1)
#define FREQ_PLL    (1)
    
    extern int g_fd_uart0;
    
    void App_Initialize();
    void App_Delay(int delay);
#ifdef	__cplusplus
}
#endif

#endif	/* PRJ */

