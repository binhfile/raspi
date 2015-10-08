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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c ucos/os_core.c ucos/os_sem.c ucos/os_flag.c ucos/os_time.c ucos/os_mem.c ucos/os_mbox.c ucos/os_q.c ucos/os_task.c ucos/os_dbg_r.c ucos/os_mutex.c ucos/ucos_ii.c ucos/os_tmr.c port/os_cpu_c.c port/vector.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/ucos/os_core.o ${OBJECTDIR}/ucos/os_sem.o ${OBJECTDIR}/ucos/os_flag.o ${OBJECTDIR}/ucos/os_time.o ${OBJECTDIR}/ucos/os_mem.o ${OBJECTDIR}/ucos/os_mbox.o ${OBJECTDIR}/ucos/os_q.o ${OBJECTDIR}/ucos/os_task.o ${OBJECTDIR}/ucos/os_dbg_r.o ${OBJECTDIR}/ucos/os_mutex.o ${OBJECTDIR}/ucos/ucos_ii.o ${OBJECTDIR}/ucos/os_tmr.o ${OBJECTDIR}/port/os_cpu_c.o ${OBJECTDIR}/port/vector.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/ucos/os_core.o.d ${OBJECTDIR}/ucos/os_sem.o.d ${OBJECTDIR}/ucos/os_flag.o.d ${OBJECTDIR}/ucos/os_time.o.d ${OBJECTDIR}/ucos/os_mem.o.d ${OBJECTDIR}/ucos/os_mbox.o.d ${OBJECTDIR}/ucos/os_q.o.d ${OBJECTDIR}/ucos/os_task.o.d ${OBJECTDIR}/ucos/os_dbg_r.o.d ${OBJECTDIR}/ucos/os_mutex.o.d ${OBJECTDIR}/ucos/ucos_ii.o.d ${OBJECTDIR}/ucos/os_tmr.o.d ${OBJECTDIR}/port/os_cpu_c.o.d ${OBJECTDIR}/port/vector.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/ucos/os_core.o ${OBJECTDIR}/ucos/os_sem.o ${OBJECTDIR}/ucos/os_flag.o ${OBJECTDIR}/ucos/os_time.o ${OBJECTDIR}/ucos/os_mem.o ${OBJECTDIR}/ucos/os_mbox.o ${OBJECTDIR}/ucos/os_q.o ${OBJECTDIR}/ucos/os_task.o ${OBJECTDIR}/ucos/os_dbg_r.o ${OBJECTDIR}/ucos/os_mutex.o ${OBJECTDIR}/ucos/ucos_ii.o ${OBJECTDIR}/ucos/os_tmr.o ${OBJECTDIR}/port/os_cpu_c.o ${OBJECTDIR}/port/vector.o

# Source Files
SOURCEFILES=main.c ucos/os_core.c ucos/os_sem.c ucos/os_flag.c ucos/os_time.c ucos/os_mem.c ucos/os_mbox.c ucos/os_q.c ucos/os_task.c ucos/os_dbg_r.c ucos/os_mutex.c ucos/ucos_ii.c ucos/os_tmr.c port/os_cpu_c.c port/vector.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K20
MP_PROCESSOR_OPTION_LD=18f46k20
MP_LINKER_DEBUG_OPTION=-r=ROM@0xFD30:0xFFFF -r=RAM@GPR:0xEF4:0xEFF -u_DEBUGSTACK
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_core.o: ucos/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_core.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_core.o   ucos/os_core.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_core.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_sem.o: ucos/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_sem.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_sem.o   ucos/os_sem.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_sem.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_flag.o: ucos/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_flag.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_flag.o   ucos/os_flag.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_flag.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_time.o: ucos/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_time.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_time.o   ucos/os_time.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_time.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_mem.o: ucos/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_mem.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_mem.o   ucos/os_mem.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_mbox.o: ucos/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_mbox.o   ucos/os_mbox.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_mbox.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_mbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_q.o: ucos/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_q.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_q.o   ucos/os_q.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_q.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_task.o: ucos/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_task.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_task.o   ucos/os_task.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_task.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_dbg_r.o: ucos/os_dbg_r.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_dbg_r.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_dbg_r.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_dbg_r.o   ucos/os_dbg_r.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_dbg_r.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_dbg_r.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_mutex.o: ucos/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_mutex.o   ucos/os_mutex.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/ucos_ii.o: ucos/ucos_ii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/ucos_ii.o.d 
	@${RM} ${OBJECTDIR}/ucos/ucos_ii.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/ucos_ii.o   ucos/ucos_ii.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/ucos_ii.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/ucos_ii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_tmr.o: ucos/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_tmr.o   ucos/os_tmr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/port/os_cpu_c.o: port/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/port 
	@${RM} ${OBJECTDIR}/port/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/port/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/port/os_cpu_c.o   port/os_cpu_c.c 
	@${DEP_GEN} -d ${OBJECTDIR}/port/os_cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/port/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/port/vector.o: port/vector.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/port 
	@${RM} ${OBJECTDIR}/port/vector.o.d 
	@${RM} ${OBJECTDIR}/port/vector.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/port/vector.o   port/vector.c 
	@${DEP_GEN} -d ${OBJECTDIR}/port/vector.o 
	@${FIXDEPS} "${OBJECTDIR}/port/vector.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_core.o: ucos/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_core.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_core.o   ucos/os_core.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_core.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_core.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_sem.o: ucos/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_sem.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_sem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_sem.o   ucos/os_sem.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_sem.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_sem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_flag.o: ucos/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_flag.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_flag.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_flag.o   ucos/os_flag.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_flag.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_flag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_time.o: ucos/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_time.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_time.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_time.o   ucos/os_time.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_time.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_time.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_mem.o: ucos/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_mem.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_mem.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_mem.o   ucos/os_mem.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_mem.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_mem.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_mbox.o: ucos/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_mbox.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_mbox.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_mbox.o   ucos/os_mbox.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_mbox.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_mbox.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_q.o: ucos/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_q.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_q.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_q.o   ucos/os_q.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_q.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_q.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_task.o: ucos/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_task.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_task.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_task.o   ucos/os_task.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_task.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_task.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_dbg_r.o: ucos/os_dbg_r.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_dbg_r.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_dbg_r.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_dbg_r.o   ucos/os_dbg_r.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_dbg_r.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_dbg_r.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_mutex.o: ucos/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_mutex.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_mutex.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_mutex.o   ucos/os_mutex.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_mutex.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_mutex.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/ucos_ii.o: ucos/ucos_ii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/ucos_ii.o.d 
	@${RM} ${OBJECTDIR}/ucos/ucos_ii.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/ucos_ii.o   ucos/ucos_ii.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/ucos_ii.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/ucos_ii.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/ucos/os_tmr.o: ucos/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/ucos 
	@${RM} ${OBJECTDIR}/ucos/os_tmr.o.d 
	@${RM} ${OBJECTDIR}/ucos/os_tmr.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/ucos/os_tmr.o   ucos/os_tmr.c 
	@${DEP_GEN} -d ${OBJECTDIR}/ucos/os_tmr.o 
	@${FIXDEPS} "${OBJECTDIR}/ucos/os_tmr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/port/os_cpu_c.o: port/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/port 
	@${RM} ${OBJECTDIR}/port/os_cpu_c.o.d 
	@${RM} ${OBJECTDIR}/port/os_cpu_c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/port/os_cpu_c.o   port/os_cpu_c.c 
	@${DEP_GEN} -d ${OBJECTDIR}/port/os_cpu_c.o 
	@${FIXDEPS} "${OBJECTDIR}/port/os_cpu_c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/port/vector.o: port/vector.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/port 
	@${RM} ${OBJECTDIR}/port/vector.o.d 
	@${RM} ${OBJECTDIR}/port/vector.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -I"ucos" -I"port" -ms -oa-  -I ${MP_CC_DIR}/../h  -fo ${OBJECTDIR}/port/vector.o   port/vector.c 
	@${DEP_GEN} -d ${OBJECTDIR}/port/vector.o 
	@${FIXDEPS} "${OBJECTDIR}/port/vector.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    uc-18f46k20.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "uc-18f46k20.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_PK3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   uc-18f46k20.lkr
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE) "uc-18f46k20.lkr"  -p$(MP_PROCESSOR_OPTION_LD)  -w  -m"${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"  -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}/../lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/test-ucos.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
