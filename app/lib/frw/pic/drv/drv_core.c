#include "drv_api.h"
#include "drv_errno.h"
#include "../frw_string.h"
#include "chip/pic24fj/drv_common.h"
int      errno = 0;
extern DRV_ELEM __drv_end;

DRV_ELEM* drv_findDrvByName(const char* pathname){
    DRV_ELEM* ret = 0;
    DRV_ELEM *elem;
    elem = &__drv_begin;
    while(elem < &__drv_end){
        if(strcmp((*elem).name, pathname) == 0){
            ret = elem;
            break;
        }
        elem++;
    }
    return ret;
}
int drv_findFdByName(const char* pathname){
    int ret = -1;
    DRV_ELEM *elem;
    int i = 0;
    elem = &__drv_begin;
    while(elem < &__drv_end){
        if(strcmp((*elem).name, pathname) == 0){
            ret = i;
            break;
        }
        elem++;
        i++;
    }
    return ret;
}
int drv_findFdByDrv(DRV_ELEM* drv){
    int ret = -1;
    DRV_ELEM *elem;
    int i = 0;
    elem = &__drv_begin;
    
    while(elem < &__drv_end){
        if(elem == drv){
            ret = i;
            break;
        }
        elem++;
        i++;
    }
    return ret;
}
DRV_ELEM* drv_findDrvByFd(int fd){
    DRV_ELEM *elem;
    elem = &__drv_begin;
    
    while(fd >= 0 && elem < &__drv_end){
        if(fd == 0){
            return elem;
        }
        fd --;
        elem ++;
    }
    return 0;
}
int drv_initialize(){
    DRV_ELEM *elem;
    elem = &__drv_begin;
    while(elem < &__drv_end){
        (*elem).opt.init();
        elem++;
    }
    return 0;
}
int open(const char *pathname, int flags){
    int ret = -EPERM;
    DRV_ELEM* drv = 0;
    
    drv = drv_findDrvByName(pathname);
    if(drv != 0){
        if(drv->opt.open){
            ret = drv->opt.open(drv, flags);
            if(ret == 0){
                ret = drv_findFdByDrv(drv);
            }
        }
        else {
            ret = -EPERM;
        }
    }
    if(ret != 0){
        errno = -ret;
        return ret;
    }
    return ret;
}
int close(int fd){
    int ret = -EPERM;
    DRV_ELEM* drv = 0;
    
    drv = drv_findDrvByFd(fd);
    if(drv != 0){
        if(drv->opt.close)
            ret = drv->opt.close(drv);
        else ret = -EPERM;
    }
    if(ret != 0){
        errno = -ret;
        return ret;
    }
    return ret;
}
//end of file
