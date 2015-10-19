#include "drv_api.h"
#include "drv_errno.h"
#include "../frw_string.h"

DRV_ELEM    *g_drvs[DRV_CORE_MAX_DEVICE] = {0};
int          g_drvCnt = 0;
int          errno = 0;

DRV_ELEM* drv_findByName(const char* pathname){
    DRV_ELEM* ret = 0;
    int i = 0;
    int found = 0;
    if(pathname){
        while(i < g_drvCnt){
            if(strcmp(g_drvs[i]->name, pathname) == 0){
                found = 1;
                break;
            }
            i++;
        }
        if(found){
            ret = g_drvs[i];
        }else{
            errno = EEXIST;
        }
    }else errno = EINVAL;
    return ret;
}
DRV_ELEM* drv_findByFd(int fd){
    if(fd >= 0 && fd < g_drvCnt){
        return g_drvs[fd];
    }
    return 0;
}
int drv_register(DRV_ELEM* drv){
    int ret = EPERM;
    int found = 0;
    int i;
    if(drv){
        // search device
        i = 0;
        while(i < g_drvCnt){
            if(g_drvs[i] == drv){
                found = 1;
                break;
            }
            i++;
        }
        if(found == 0){
            g_drvs[g_drvCnt] = drv;
            g_drvCnt ++;
        }else ret = EEXIST;
    }else ret = EINVAL;
    errno = ret;
    return -ret;
}
int open(const char *pathname, int flags){
    int ret = EPERM;
    DRV_ELEM* drv = 0;
    
    drv = drv_findByName(pathname);
    if(drv != 0){
        if(drv->opt.open)
            ret = drv->opt.open(drv, flags);
        else {
            ret = EPERM;
        }
    }
    errno = ret;
    return -ret;
}
int close(int fd){
    int ret = EPERM;
    DRV_ELEM* drv = 0;
    
    drv = drv_findByFd(fd);
    if(drv != 0){
        if(drv->opt.close)
            ret = drv->opt.close(drv);
        else ret = EPERM;
    }
    errno = ret;
    return -ret;
}
//ssize_t read(int fd, void* buf, size_t count){
//    return ((DRV_ELEM* )(g_drvHead + fd))->opt->read((g_drvHead + fd), buf, count);
//}
//ssize_t write(int fd, void* buf, size_t count){
//    ssize_t ret = -1;
//    DRV_ELEM* drv = 0;
//    
//    drv = drv_findFromFd(fd);
//    if(drv != 0){
//        if(drv->opt->write)
//            ret = drv->opt->write(drv, buf, count);
//        else
//            errno = EPERM;
//    }else{
//        errno = ENXIO;
//    }
//    return ret;
//}
//int ioctl(int fd, int request, unsigned int arguments){
//    int ret = -1;
//    DRV_ELEM* drv = 0;
//    
//    drv = drv_findFromFd(fd);
//    if(drv != 0){
//        if(drv->opt->ioctl)
//            ret = drv->opt->ioctl(drv, request, arguments);
//        else
//            errno = EPERM;
//    }else
//        errno = ENXIO;
//    return ret;
//}
//end of file
