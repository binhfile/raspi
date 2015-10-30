APPNAME=pic24fj
CHIP=24FJ128GA106
ROOT=../../
PROJECT=./
CROSS_COMPILE=xc16-
CROSS_COMPILE_ROOT=/opt/microchip/xc16/v1.25

DEFINEDS=

LDFLAGS=-mcpu=$(CHIP) -omf=elf -Wl,,--defsym=__MPLAB_BUILD=1,,--script=src/pic24fj.gld,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="production.map",--report-mem,--memorysummary,memoryfile.xml
CFLAGS=-mcpu=$(CHIP) -MMD -g -omf=elf -mlarge-code -mlarge-data -mlarge-scalar -O1 -msmart-io=1 -Wall -msfr-warn=off
CC=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)gcc
BIN2HEX=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)bin2hex
STRIP=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)strip
OBJDUMP=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)objdump
PROGRAM=/opt/microchip/mplabx/v3.10/mplab_ide/bin/mdb.sh
PROGRAM_CMD=program_cmd.txt
PREFIX=@
OBJS=

# MLA
INCLUDES+=-Isrc/miwi
INCLUDES+=-I$(ROOT)/third-party/mla/framework
OBJS+= \
$(ROOT)/third-party/mla/framework/miwi/src/miwi_nvm.o\
$(ROOT)/third-party/mla/framework/miwi/src/miwi_p2p.o\

# UCOS port
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/CustomBoard
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uCOS-II/Source
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uC-LIB
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uC-CPU
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uC-CPU/Microchip/XC16
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uC-LIB/Cfg/Template
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uCOS-II/Cfg/Template
INCLUDES+=-I$(ROOT)/third-party/Micrium/Software/uC-CPU/Cfg/Template
OBJS+= \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.o \
$(ROOT)/third-party/Micrium/Software/CustomBoard/bsp.o \
$(ROOT)/third-party/Micrium/Software/CustomBoard/bsp_a.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_core.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_mbox.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_flag.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_mem.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_mutex.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_q.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_sem.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_task.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_time.o \
$(ROOT)/third-party/Micrium/Software/uCOS-II/Source/os_tmr.o \

# User code
INCLUDES+=-I$(ROOT)/lib/include
INCLUDES+=-I$(ROOT)/lib/frw/pic
INCLUDES+=-I$(ROOT)/lib/frw/pic/ucos/include

OBJS+= \
src/main.o \
src/chip_cfg.o \
src/prj_cfg.o \
$(ROOT)/lib/src/lib_debug.o \
$(ROOT)/lib/frw/pic/drv/drv_core.o \
$(ROOT)/lib/frw/pic/drv/chip/pic24fj/drv_utils.o \
$(ROOT)/lib/frw/pic/drv/chip/pic24fj/drv_uart.o \
$(ROOT)/lib/frw/pic/drv/chip/pic24fj/drv_common.o \
$(ROOT)/lib/frw/pic/drv/chip/pic24fj/drv_gpio.o \
$(ROOT)/lib/frw/pic/drv/chip/pic24fj/drv_ext_intr.o \
$(ROOT)/lib/frw/pic/drv/chip/pic24fj/drv_spi.o \
$(ROOT)/lib/frw/pic/frw_string.o \
$(ROOT)/lib/frw/pic/ucos/src/unistd.o \
$(ROOT)/lib/frw/pic/ucos/src/pthread.o \
$(ROOT)/lib/frw/pic/ucos/src/semaphore.o \

#$(PREFIX) $(STRIP) --strip-all $(APPNAME)
all:$(OBJS)
	$(PREFIX) echo [LD] $(APPNAME)
	$(PREFIX) $(CC) *.o -o $(APPNAME).elf $(LDFLAGS)
	$(PREFIX) $(BIN2HEX) $(APPNAME).elf -a  -omf=elf
	$(PREFIX) $(OBJDUMP) -S $(APPNAME).elf > $(APPNAME).lst
	$(PREFIX) $(RM) *.o *.d
	$(PREFIX) echo DONE
%.o:%.c
	$(PREFIX) echo [CC] $<
	$(PREFIX) $(CC) -c $< $(CFLAGS) $(DEFINEDS) $(INCLUDES)
%.o:%.s
	$(PREFIX) echo [AS] $<
	$(PREFIX) $(CC) -c $< $(CFLAGS) $(DEFINEDS) $(INCLUDES)
clean:
	$(PREFIX) echo [RM] $(OBJS) $(APPNAME)
	$(PREFIX) $(RM) *.o
	$(PREFIX) $(RM) $(APPNAME)
prog:
	$(PREFIX) $(PROGRAM) $(PROGRAM_CMD)
	$(PREFIX) $(RM) MPLABXLog.xml*
	$(PREFIX) echo DONE
	