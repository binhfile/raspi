/* 
 * File:   unistd.h
 * Author: dev
 *
 * Created on October 26, 2015, 10:04 AM
 */

#ifndef UNISTD_H
#define	UNISTD_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#ifndef __useconds_t
#define __useconds_t    uint32_t
#endif
unsigned int sleep (unsigned int __seconds);
int msleep (unsigned int __useconds);


#ifdef	__cplusplus
}
#endif

#endif	/* UNISTD_H */

