#include "drv_gpio.h"
#include "../../drv_api.h"
#include "drv_regs.h"
#include "../../../frw_string.h"
#include <xc.h>
struct DRV_GPIO{
    DRV_ELEM drv;
};
int drv_gpio_init();
int drv_gpio_open(void *drv, int flags);
int drv_gpio_close(void *drv);
int drv_gpio_ioctl(void *drv, int request, unsigned int arguments);

const char      g_drv_gpio_name[] = "gpio";
struct DRV_GPIO g_drv_gpio = {
    .drv.opt.init   = drv_gpio_init,
    .drv.opt.open   = drv_gpio_open,
    .drv.opt.close  = drv_gpio_close,
    .drv.opt.ioctl  = drv_gpio_ioctl,
};
DRV_REGISTER(g_drv_gpio);
int drv_gpio_init(){
    g_drv_gpio.drv.name = g_drv_gpio_name;
    return 0;
}
int drv_gpio_open(void *drv, int flags){
    return 0;
}
int drv_gpio_close(void *drv){
    return 0;
}
int drv_gpio_enable_pin(struct DRV_GPIO* drv, struct DRV_GPIO_ENABLE* arg){
    int ret = -1;
    unsigned int port, pin;
    unsigned int base_reg;
    port = arg->pin >> 4;
    pin  = arg->pin % 16;
    base_reg = GPIO_REG_BASE_ADDR + (GPIO_REG_MODULE_LEN * port);
    REG(base_reg + GPIO_REG_TRIS) = 
            (REG(base_reg + GPIO_REG_TRIS) & 
            (~((unsigned int)(0x01) << pin))) |
            ((unsigned int)(arg->dir) << pin);
    REG(base_reg + GPIO_REG_ODC) = 
            (REG(base_reg + GPIO_REG_ODC) & 
            (~((unsigned int)(0x01) << pin))) |
            ((unsigned int)(arg->opendrain) << pin);
    // analog port for B0-B15 (1*16+0 + 1*16+15)
    if(port == 1){  // port B
        REG(ADC_REG_BASE_ADDR + ADC_REG_AD1PCFGL) = 
                REG(ADC_REG_BASE_ADDR + ADC_REG_AD1PCFGL) | (((unsigned int)1) << pin);
    }
    Nop();
    ret = 0;
    return ret;    
}
int drv_gpio_write_pin(struct DRV_GPIO* drv, struct DRV_GPIO_WRITE* arg){
    unsigned int port, pin;
    unsigned int base_reg;
    port = arg->pin >> 4;
    pin  = arg->pin % 16;
    base_reg = GPIO_REG_BASE_ADDR + (GPIO_REG_MODULE_LEN * port);
    REG(base_reg + GPIO_REG_LAT) = 
            (REG(base_reg + GPIO_REG_LAT) & 
            (~((unsigned int)(0x01) << pin))) |
            ((unsigned int)(arg->value) << pin);
    return 0;   
}
int drv_gpio_read_pin(struct DRV_GPIO* drv, struct DRV_GPIO_READ* arg){
    unsigned int port, pin;
    unsigned int base_reg;
    port = arg->pin >> 4;
    pin  = arg->pin % 16;
    base_reg = GPIO_REG_BASE_ADDR + (GPIO_REG_MODULE_LEN * port);
    arg->value = (REG(base_reg + GPIO_REG_PORT) >> pin) & (unsigned int)(0x01);
    return 0;
}
int drv_gpio_set_icn(struct DRV_GPIO* drv, struct DRV_GPIO_INPUT_CHANGE_NOTIFICATION* arg){
    int ret = -1;
    unsigned int reg_index, offset;
    unsigned int reg;
    reg_index = arg->cn_pin >> 4;
    offset  = arg->cn_pin % 16;
    // enable
    reg = ICN_REG_BASE_ADDR + ICN_REG_CNEN + (reg_index << 1);
    REG(reg) = (REG(reg) & 
            (~(((unsigned int)0x01) << offset))) |
            (((arg->enable == 0) ? 0 : 1) << offset);
    reg = ICN_REG_BASE_ADDR + ICN_REG_CNPD + (reg_index << 1);
    REG(reg) = (REG(reg) & 
            (~(((unsigned int)0x01) << offset))) |
            (((arg->pull_down == 0) ? 0 : 1) << offset);
    reg = ICN_REG_BASE_ADDR + ICN_REG_CNPU + (reg_index << 1);
    REG(reg) = (REG(reg) & 
            (~(((unsigned int)0x01) << offset))) |
            (((arg->pull_up == 0) ? 0 : 1) << offset);
    ret = 0;
    
    return ret;
}
int drv_gpio_ioctl(void *drv, int request, unsigned int arguments){
    int ret = -1;
    
    switch(request){
        case DRV_GPIO_IOCTL_WRITE:
            ret = drv_gpio_write_pin(drv, (struct DRV_GPIO_WRITE*)arguments);
            break;
        case DRV_GPIO_IOCTL_READ:
            ret = drv_gpio_read_pin(drv, (struct DRV_GPIO_READ*)arguments);
            break;
        case DRV_GPIO_IOCTL_ENABLE:
            ret = drv_gpio_enable_pin(drv, (struct DRV_GPIO_ENABLE*)arguments);
            break;
        case DRV_GPIO_IOCTL_SET_ICN:
            ret = drv_gpio_set_icn(drv, (struct DRV_GPIO_INPUT_CHANGE_NOTIFICATION*)arguments);
            break;
    }
    return ret;
}
// end of file
