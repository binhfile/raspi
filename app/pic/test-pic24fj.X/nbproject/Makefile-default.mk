#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../../lib/frw/pic/drv/drv_core.c ../../lib/frw/pic/drv/chip/pic24fj/drv_uart.c ../../lib/frw/pic/frw_string.c ../../lib/src/lib_debug.c src/main.c src/chip_cfg.c ../../third-party/Micrium/Software/uCOS-II/Source/os_core.c ../../third-party/Micrium/Software/uCOS-II/Source/os_flag.c ../../third-party/Micrium/Software/uCOS-II/Source/os_mbox.c ../../third-party/Micrium/Software/uCOS-II/Source/os_mem.c ../../third-party/Micrium/Software/uCOS-II/Source/os_mutex.c ../../third-party/Micrium/Software/uCOS-II/Source/os_q.c ../../third-party/Micrium/Software/uCOS-II/Source/os_sem.c ../../third-party/Micrium/Software/uCOS-II/Source/os_task.c ../../third-party/Micrium/Software/uCOS-II/Source/os_time.c ../../third-party/Micrium/Software/uCOS-II/Source/os_tmr.c src/prj_cfg.c ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.s ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.c ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/454452373/drv_core.o ${OBJECTDIR}/_ext/1912918919/drv_uart.o ${OBJECTDIR}/_ext/353607548/frw_string.o ${OBJECTDIR}/_ext/957557178/lib_debug.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/chip_cfg.o ${OBJECTDIR}/_ext/1496000527/os_core.o ${OBJECTDIR}/_ext/1496000527/os_flag.o ${OBJECTDIR}/_ext/1496000527/os_mbox.o ${OBJECTDIR}/_ext/1496000527/os_mem.o ${OBJECTDIR}/_ext/1496000527/os_mutex.o ${OBJECTDIR}/_ext/1496000527/os_q.o ${OBJECTDIR}/_ext/1496000527/os_sem.o ${OBJECTDIR}/_ext/1496000527/os_task.o ${OBJECTDIR}/_ext/1496000527/os_time.o ${OBJECTDIR}/_ext/1496000527/os_tmr.o ${OBJECTDIR}/src/prj_cfg.o ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/454452373/drv_core.o.d ${OBJECTDIR}/_ext/1912918919/drv_uart.o.d ${OBJECTDIR}/_ext/353607548/frw_string.o.d ${OBJECTDIR}/_ext/957557178/lib_debug.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/chip_cfg.o.d ${OBJECTDIR}/_ext/1496000527/os_core.o.d ${OBJECTDIR}/_ext/1496000527/os_flag.o.d ${OBJECTDIR}/_ext/1496000527/os_mbox.o.d ${OBJECTDIR}/_ext/1496000527/os_mem.o.d ${OBJECTDIR}/_ext/1496000527/os_mutex.o.d ${OBJECTDIR}/_ext/1496000527/os_q.o.d ${OBJECTDIR}/_ext/1496000527/os_sem.o.d ${OBJECTDIR}/_ext/1496000527/os_task.o.d ${OBJECTDIR}/_ext/1496000527/os_time.o.d ${OBJECTDIR}/_ext/1496000527/os_tmr.o.d ${OBJECTDIR}/src/prj_cfg.o.d ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/454452373/drv_core.o ${OBJECTDIR}/_ext/1912918919/drv_uart.o ${OBJECTDIR}/_ext/353607548/frw_string.o ${OBJECTDIR}/_ext/957557178/lib_debug.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/chip_cfg.o ${OBJECTDIR}/_ext/1496000527/os_core.o ${OBJECTDIR}/_ext/1496000527/os_flag.o ${OBJECTDIR}/_ext/1496000527/os_mbox.o ${OBJECTDIR}/_ext/1496000527/os_mem.o ${OBJECTDIR}/_ext/1496000527/os_mutex.o ${OBJECTDIR}/_ext/1496000527/os_q.o ${OBJECTDIR}/_ext/1496000527/os_sem.o ${OBJECTDIR}/_ext/1496000527/os_task.o ${OBJECTDIR}/_ext/1496000527/os_time.o ${OBJECTDIR}/_ext/1496000527/os_tmr.o ${OBJECTDIR}/src/prj_cfg.o ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o

# Source Files
SOURCEFILES=../../lib/frw/pic/drv/drv_core.c ../../lib/frw/pic/drv/chip/pic24fj/drv_uart.c ../../lib/frw/pic/frw_string.c ../../lib/src/lib_debug.c src/main.c src/chip_cfg.c ../../third-party/Micrium/Software/uCOS-II/Source/os_core.c ../../third-party/Micrium/Software/uCOS-II/Source/os_flag.c ../../third-party/Micrium/Software/uCOS-II/Source/os_mbox.c ../../third-party/Micrium/Software/uCOS-II/Source/os_mem.c ../../third-party/Micrium/Software/uCOS-II/Source/os_mutex.c ../../third-party/Micrium/Software/uCOS-II/Source/os_q.c ../../third-party/Micrium/Software/uCOS-II/Source/os_sem.c ../../third-party/Micrium/Software/uCOS-II/Source/os_task.c ../../third-party/Micrium/Software/uCOS-II/Source/os_time.c ../../third-party/Micrium/Software/uCOS-II/Source/os_tmr.c src/prj_cfg.c ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.s ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.c ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=24FJ128GA106
MP_LINKER_FILE_OPTION=,--script=p24FJ128GA106.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/454452373/drv_core.o: ../../lib/frw/pic/drv/drv_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/454452373" 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/drv_core.c  -o ${OBJECTDIR}/_ext/454452373/drv_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/454452373/drv_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/454452373/drv_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1912918919/drv_uart.o: ../../lib/frw/pic/drv/chip/pic24fj/drv_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1912918919" 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/chip/pic24fj/drv_uart.c  -o ${OBJECTDIR}/_ext/1912918919/drv_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1912918919/drv_uart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1912918919/drv_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/353607548/frw_string.o: ../../lib/frw/pic/frw_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/353607548" 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/frw_string.c  -o ${OBJECTDIR}/_ext/353607548/frw_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/353607548/frw_string.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/353607548/frw_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/957557178/lib_debug.o: ../../lib/src/lib_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/957557178" 
	@${RM} ${OBJECTDIR}/_ext/957557178/lib_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/957557178/lib_debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/src/lib_debug.c  -o ${OBJECTDIR}/_ext/957557178/lib_debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/957557178/lib_debug.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/957557178/lib_debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/chip_cfg.o: src/chip_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/chip_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/chip_cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/chip_cfg.c  -o ${OBJECTDIR}/src/chip_cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/chip_cfg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/chip_cfg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_core.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_core.c  -o ${OBJECTDIR}/_ext/1496000527/os_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_flag.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_flag.c  -o ${OBJECTDIR}/_ext/1496000527/os_flag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_flag.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_flag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_mbox.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_mbox.c  -o ${OBJECTDIR}/_ext/1496000527/os_mbox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_mbox.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_mbox.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_mem.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_mem.c  -o ${OBJECTDIR}/_ext/1496000527/os_mem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_mem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_mem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_mutex.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_mutex.c  -o ${OBJECTDIR}/_ext/1496000527/os_mutex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_mutex.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_mutex.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_q.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_q.c  -o ${OBJECTDIR}/_ext/1496000527/os_q.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_q.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_q.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_sem.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_sem.c  -o ${OBJECTDIR}/_ext/1496000527/os_sem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_sem.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_sem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_task.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_task.c  -o ${OBJECTDIR}/_ext/1496000527/os_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_task.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_time.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_time.c  -o ${OBJECTDIR}/_ext/1496000527/os_time.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_time.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_time.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_tmr.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_tmr.c  -o ${OBJECTDIR}/_ext/1496000527/os_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_tmr.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_tmr.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/prj_cfg.o: src/prj_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/prj_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/prj_cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/prj_cfg.c  -o ${OBJECTDIR}/src/prj_cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/prj_cfg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/prj_cfg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1258168160/os_cpu_c.o: ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1258168160" 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  -o ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/454452373/drv_core.o: ../../lib/frw/pic/drv/drv_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/454452373" 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/drv_core.c  -o ${OBJECTDIR}/_ext/454452373/drv_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/454452373/drv_core.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/454452373/drv_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1912918919/drv_uart.o: ../../lib/frw/pic/drv/chip/pic24fj/drv_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1912918919" 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_uart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/chip/pic24fj/drv_uart.c  -o ${OBJECTDIR}/_ext/1912918919/drv_uart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1912918919/drv_uart.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1912918919/drv_uart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/353607548/frw_string.o: ../../lib/frw/pic/frw_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/353607548" 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/frw_string.c  -o ${OBJECTDIR}/_ext/353607548/frw_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/353607548/frw_string.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/353607548/frw_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/957557178/lib_debug.o: ../../lib/src/lib_debug.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/957557178" 
	@${RM} ${OBJECTDIR}/_ext/957557178/lib_debug.o.d 
	@${RM} ${OBJECTDIR}/_ext/957557178/lib_debug.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/src/lib_debug.c  -o ${OBJECTDIR}/_ext/957557178/lib_debug.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/957557178/lib_debug.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/957557178/lib_debug.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/chip_cfg.o: src/chip_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/chip_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/chip_cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/chip_cfg.c  -o ${OBJECTDIR}/src/chip_cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/chip_cfg.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/chip_cfg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_core.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_core.c  -o ${OBJECTDIR}/_ext/1496000527/os_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_core.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_flag.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_flag.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_flag.c  -o ${OBJECTDIR}/_ext/1496000527/os_flag.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_flag.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_flag.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_mbox.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_mbox.c  -o ${OBJECTDIR}/_ext/1496000527/os_mbox.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_mbox.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_mbox.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_mem.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_mem.c  -o ${OBJECTDIR}/_ext/1496000527/os_mem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_mem.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_mem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_mutex.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_mutex.c  -o ${OBJECTDIR}/_ext/1496000527/os_mutex.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_mutex.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_mutex.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_q.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_q.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_q.c  -o ${OBJECTDIR}/_ext/1496000527/os_q.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_q.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_q.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_sem.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_sem.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_sem.c  -o ${OBJECTDIR}/_ext/1496000527/os_sem.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_sem.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_sem.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_task.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_task.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_task.c  -o ${OBJECTDIR}/_ext/1496000527/os_task.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_task.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_task.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_time.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_time.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_time.c  -o ${OBJECTDIR}/_ext/1496000527/os_time.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_time.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_time.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1496000527/os_tmr.o: ../../third-party/Micrium/Software/uCOS-II/Source/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1496000527" 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/_ext/1496000527/os_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Source/os_tmr.c  -o ${OBJECTDIR}/_ext/1496000527/os_tmr.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1496000527/os_tmr.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1496000527/os_tmr.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/prj_cfg.o: src/prj_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/prj_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/prj_cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/prj_cfg.c  -o ${OBJECTDIR}/src/prj_cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/prj_cfg.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/prj_cfg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1258168160/os_cpu_c.o: ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1258168160" 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_c.c  -o ${OBJECTDIR}/_ext/1258168160/os_cpu_c.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -I"../../lib/include" -I"../../third-party/Micrium/Software/uCOS-II/Source" -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-LIB" -I"../../third-party/Micrium/Software/uC-CPU" -I"../../third-party/Micrium/Software/uC-CPU/Microchip/XC16" -I"../../third-party/Micrium/Software/uC-CPU/Cfg/Template" -I"../../third-party/Micrium/Software/uC-LIB/Cfg/Template" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/BSP" -I"../../third-party/Micrium/Software/EvalBoards/Microchip/Explorer16/XC16/OS-Probe" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1258168160/os_cpu_c.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1258168160/os_cpu_a.o: ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1258168160" 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  -o ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o: ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1258168160" 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  -o ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/1258168160/os_cpu_a.o: ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1258168160" 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_a.s  -o ${OBJECTDIR}/_ext/1258168160/os_cpu_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=coff -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1258168160/os_cpu_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o: ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1258168160" 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d 
	@${RM} ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  ../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16/os_cpu_util_a.s  -o ${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=coff -I"../../third-party/Micrium/Software/uCOS-II/Ports/Microchip/XC16" -Wa,-MD,"${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/1258168160/os_cpu_util_a.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff  -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=coff -Wl,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/test-pic24fj.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
