APPNAME=coordinator
MAKE_DEFINEDS+=DEBUG
#MAKE_DEFINEDS+=GDB
ROOT=../../
PROJECT=./
CROSS_COMPILE=bcm2708-
CROSS_COMPILE_ROOT=/home/toolchain/tools-master/arm-bcm2708/arm-bcm2708-linux-gnueabi
CROSS_COMPILE_SYSROOT=$(CROSS_COMPILE_ROOT)/arm-bcm2708-linux-gnueabi/sysroot
EXTRA_LIB=$(ROOT)/lib
ZIG_LIB=$(ROOT)/ziglib
MCP_ZIGBEE=$(ROOT)/MPZigBee

#ifneq (,$(findstring RELEASE,$(MAKE_DEFINEDS)))
#    DEFINEDS+=-D_RELEASE_=1
#    DEFINEDS+=-DLREP_DISABLE=1
#endif
#ifneq (,$(findstring DEBUG,$(MAKE_DEFINEDS)))
#    DEFINEDS+=-D_DEBUG_=1
#    CFLAGS=-ggdb -g3
#	CPPFLAGS=-ggdb -g3
#endif

DEFINEDS=
LDFLAGS=-lpthread -lrt -ldl --sysroot=$(CROSS_COMPILE_SYSROOT)
CFLAGS+=--sysroot=$(CROSS_COMPILE_SYSROOT) -fstack-protector -ggdb -g3 -O0
CPPFLAGS+=--sysroot=$(CROSS_COMPILE_SYSROOT) -fstack-protector -ggdb -g3 -O0
CC=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)gcc
CPP=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)g++
STRIP=$(CROSS_COMPILE_ROOT)/bin/$(CROSS_COMPILE)strip
#ifneq (,$(findstring GDB,$(MAKE_DEFINEDS)))
#	CFLAGS+=-ggdb -g3
#	CPPFLAGS+=-ggdb -g3
#	STRIP_CMD=echo BUILD FOR GDB
#else
#	CFLAGS+=-O2
#	CPPFLAGS+=-O2
#	STRIP_CMD=$(PREFIX) $(STRIP) --strip-all $(APPNAME)	
#endif
PREFIX=@
OBJS=

INCLUDES+=-I$(PROJECT)/src
INCLUDES+=-I$(EXTRA_LIB)/include
INCLUDES+=-I$(EXTRA_LIB)/drivers
INCLUDES+=-I$(EXTRA_LIB)/hwl/bcm2835
INCLUDES+=-I$(ZIG_LIB)
INCLUDES+=-I$(MCP_ZIGBEE)/ZigBeeStack
INCLUDES+=-I$(MCP_ZIGBEE)/Common

OBJS+= \
$(MCP_ZIGBEE)/ZigBeeStack/zZDO.o \
$(MCP_ZIGBEE)/ZigBeeStack/zSecurity_MRF24J40.o \
$(MCP_ZIGBEE)/ZigBeeStack/zPHY_MRF24J40.o \
$(MCP_ZIGBEE)/ZigBeeStack/zNWK.o \
$(MCP_ZIGBEE)/ZigBeeStack/zNVM.o \
$(MCP_ZIGBEE)/ZigBeeStack/zMAC_MRF24J40.o \
$(MCP_ZIGBEE)/ZigBeeStack/ZigbeeTasks.o \
$(MCP_ZIGBEE)/ZigBeeStack/zAPS.o \
$(MCP_ZIGBEE)/ZigBeeStack/SymbolTime.o \
$(MCP_ZIGBEE)/Common/sralloc.o

OBJS+= \
src/main.o \
src/myZigBee.o \
$(EXTRA_LIB)/src/lib_mem.o \
$(EXTRA_LIB)/src/lib_debug.o \
$(EXTRA_LIB)/src/lib_gpio.o \
$(EXTRA_LIB)/src/lib_spi.o \
$(EXTRA_LIB)/src/lib_sem.o \
$(EXTRA_LIB)/src/lib_thread.o \
$(EXTRA_LIB)/src/lib_time.o \
$(EXTRA_LIB)/frw/linux/frw_debug_stdout.o \
$(EXTRA_LIB)/frw/linux/frw_gpio_sysfs.o \
$(EXTRA_LIB)/frw/linux/frw_mem.o \
$(EXTRA_LIB)/frw/linux/frw_spi.o \
$(EXTRA_LIB)/frw/linux/frw_sem.o \
$(EXTRA_LIB)/frw/linux/frw_thread.o \
$(EXTRA_LIB)/frw/linux/frw_time.o \
$(EXTRA_LIB)/drivers/mrf24j40/mrf24j40.o

#$(PREFIX) $(STRIP) --strip-all $(APPNAME)
all:$(OBJS)
	$(PREFIX) echo [LD] $(APPNAME)
	$(PREFIX) $(CPP) *.o -o $(APPNAME) $(LDFLAGS)
	$(PREFIX) $(RM) *.o	
%.o:%.cpp
	$(PREFIX) echo [CPP] $<
	$(PREFIX) $(CPP) -c $< $(CPPFLAGS) $(DEFINEDS) $(INCLUDES)
%.o:%.c
	$(PREFIX) echo [CC] $<
	$(PREFIX) $(CC) -c $< $(CFLAGS) $(DEFINEDS) $(INCLUDES)
clean:
	$(PREFIX) echo [RM] $(OBJS) $(APPNAME)
	$(PREFIX) $(RM) *.o
	$(PREFIX) $(RM) $(APPNAME)
	