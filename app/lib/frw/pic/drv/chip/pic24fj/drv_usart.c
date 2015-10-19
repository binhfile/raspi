#include "drv_usart.h"
#include "../../drv_api.h"
#include <frw_string.h>

struct DRV_USART{
    int         index;
    DRV_ELEM    drv;
};
//const char          *g_usart_name[] = {"usart0"};
//struct DRV_USART     g_usart[1];

int drv_usart_open(void *drv, int flags){
    int ret = -1;
    struct DRV_USART* _drv;
    
    _drv = container_of(drv, struct DRV_USART, drv);
    if(_drv->index == 0){
        
    }
    return ret;
}
int drv_usart_close(void *drv){
    int ret = -1;
    return ret;
}
ssize_t drv_usart_read(void *drv, void* buf, size_t count){
    ssize_t ret = -1;
    return ret;
}
ssize_t drv_usart_write(void *drv, void* buf, size_t count){
    ssize_t ret = -1;
    return ret;    
}
int drv_usart_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    struct termios2 *opt;
    struct DRV_USART* _drv;
    _drv = container_of(drv, struct DRV_USART, drv);
    if(request == TCGETS2){
        opt = (struct termios2*)arguments;
        if(_drv->index == 0){
            memset(opt, 0, sizeof(struct termios2));
            ret = 0;
        }
    }else if(request == TCSETS2){
        opt = (struct termios2*)arguments;
        if(_drv->index == 0){
            //opt->c_ispeed
        }
    }
    return ret;
}
#define DRV_USART_MODULE_CNT    1
const char          *g_usart_name[DRV_USART_MODULE_CNT] = {"usart0"};
struct DRV_USART     g_usart[DRV_USART_MODULE_CNT] = {
    {
      .index            = 0,  
      .drv.opt.open     = drv_usart_open,
      .drv.opt.close    = drv_usart_close,
      .drv.opt.read     = drv_usart_read,
      .drv.opt.write    = drv_usart_write,
      .drv.opt.ioctl    = drv_usart_ioctl,
    },
};
int drv_usartInitialize(){
    int ret = 0, i;
    for(i = 0; i < DRV_USART_MODULE_CNT; i++){
        g_usart[i].drv.name = g_usart_name[i];
        drv_register(&g_usart[i].drv);
    }
    return ret;
}
// end of file
