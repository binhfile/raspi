/* 
 * File:   drv_api.h
 * Author: dev
 *
 * Created on October 19, 2015, 11:20 AM
 */

#ifndef DRV_API_H
#define	DRV_API_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_errno.h"
#ifndef ssize_t
#define ssize_t     int
#endif
#ifndef size_t
#define size_t      unsigned int
#endif
#ifndef INT8
#define INT8        char
#endif
#ifndef UINT8
#define UINT8       unsigned char
#endif
#ifndef INT16
#define INT16       short
#endif
#ifndef UINT16
#define UINT16      unsigned short
#endif
#ifndef INT32
#define INT32       long long
#endif
#ifndef UINT32
#define UINT32       unsigned long long
#endif
typedef int (*DRV_INIT)();
typedef int (*DRV_RELEASE)();
typedef int (*DRV_OPEN)(void *drv, int flags);
typedef int (*DRV_CLOSE)(void *drv);
typedef ssize_t (*DRV_READ)(void *drv, void* buf, size_t count);
typedef ssize_t (*DRV_WRITE)(void *drv, const void* buf, size_t count);
/**
 * @return
 * @retval 0 : timeout
 * @retval negative: error
 * @retval positive: interrupt fired, return interrupt flag
 */
typedef int (*DRV_POLL)(void *drv, int timeout);
typedef int (*DRV_IOCTL)(void *drv, int request, unsigned int arguments);
typedef struct{
    DRV_INIT        init;
    DRV_RELEASE     release;
    DRV_OPEN        open;
    DRV_CLOSE       close;
    DRV_READ        read;
    DRV_WRITE       write;
    DRV_IOCTL       ioctl;
    DRV_POLL        poll;
}DRV_OPERATIONS;
typedef struct{
    DRV_OPERATIONS   opt;
    const char      *name;
}DRV_ELEM;

extern int errno;
extern DRV_ELEM     __drv_begin;

int drv_initialize();
int drv_findFdByName(const char* pathname);
/**
 * @brief Create a new open file description, an entry in the system-wide table of open files.
 * @param pathname  Path name for a file
 * @param flags     
 * @return Return new file descriptor, -1 if an error occurred, errno is set
 */
int open(const char *pathname, int flags);
/**
 * @brief Closes a file descriptor, so that it no longer refers to any file and may be reused
 * @param fd        File descriptor
 * @return          Return new file descriptor, -1 if an error occurred, errno is set
 */
int close(int fd);
/**
 * @brief Read up to count bytes from file descriptor fd into the buffer starting at buf
 * @param fd        File descriptor
 * @param buf       Buffer
 * @param count     Count bytes
 * @return Number of bytes read, -1 if an error occurred, errno is set
 */
//    ssize_t read(int fd, void* buf, size_t count);
#define read(fd, buf, count) \
    (*(((DRV_ELEM*)(&__drv_begin)) + fd)).opt.read((((DRV_ELEM*)(&__drv_begin)) + fd), buf, count)
    /**
     * @brief Writes  up  to count bytes from the buffer pointed buf to the file referred to by the file descriptor fd.
     * @param fd        File descriptor
     * @param buf       Buffer
     * @param count     Count bytes
     * @return          Number of bytes written, -1 if an error occurred, error is set
     */
//    ssize_t write(int fd, void* buf, size_t count);
#define write(fd, buf, count) \
    (*(((DRV_ELEM*)(&__drv_begin)) + fd)).opt.write((((DRV_ELEM*)(&__drv_begin)) + fd), buf, count)
    /**
     * @brief Function manipulates the underlying device parameters of special files.
     * @param fd        File descriptor
     * @param request   Request value
     * @return Usually,  on success zero is returned. 
     *  A few ioctl() requests use the return value as an output parameter and
     *  return a nonnegative value on success.
     *  On error, -1 is returned, and errno is set appropriately.
     */ 
//    int ioctl(int fd, int request, unsigned int arguments);
#define ioctl(fd, request, arguments)  \
    (*(((DRV_ELEM*)(&__drv_begin)) + fd)).opt.ioctl((((DRV_ELEM*)(&__drv_begin)) + fd), request, arguments)

#define poll(fd, timeout)  \
    (*(((DRV_ELEM*)(&__drv_begin)) + fd)).opt.poll((((DRV_ELEM*)(&__drv_begin)) + fd), timeout)
        
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) (type *)(((size_t)ptr) - offsetof(type, member))

#define DRV_REGISTER(elem) DRV_ELEM* drv_elem_##elem __attribute__((__section__(".drv"))) = (DRV_ELEM*)&elem

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_API_H */

