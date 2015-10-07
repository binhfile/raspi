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
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/ucos/os_core.c src/ucos/os_sem.c src/ucos/os_flag.c src/ucos/os_time.c src/ucos/os_mem.c src/ucos/os_mbox.c src/ucos/os_q.c src/ucos/os_task.c src/ucos/os_dbg_r.c src/ucos/os_mutex.c src/ucos/ucos_ii.c src/ucos/os_tmr.c main.c src/os_cpu_c.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/ucos/os_core.p1 ${OBJECTDIR}/src/ucos/os_sem.p1 ${OBJECTDIR}/src/ucos/os_flag.p1 ${OBJECTDIR}/src/ucos/os_time.p1 ${OBJECTDIR}/src/ucos/os_mem.p1 ${OBJECTDIR}/src/ucos/os_mbox.p1 ${OBJECTDIR}/src/ucos/os_q.p1 ${OBJECTDIR}/src/ucos/os_task.p1 ${OBJECTDIR}/src/ucos/os_dbg_r.p1 ${OBJECTDIR}/src/ucos/os_mutex.p1 ${OBJECTDIR}/src/ucos/ucos_ii.p1 ${OBJECTDIR}/src/ucos/os_tmr.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/src/os_cpu_c.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/ucos/os_core.p1.d ${OBJECTDIR}/src/ucos/os_sem.p1.d ${OBJECTDIR}/src/ucos/os_flag.p1.d ${OBJECTDIR}/src/ucos/os_time.p1.d ${OBJECTDIR}/src/ucos/os_mem.p1.d ${OBJECTDIR}/src/ucos/os_mbox.p1.d ${OBJECTDIR}/src/ucos/os_q.p1.d ${OBJECTDIR}/src/ucos/os_task.p1.d ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d ${OBJECTDIR}/src/ucos/os_mutex.p1.d ${OBJECTDIR}/src/ucos/ucos_ii.p1.d ${OBJECTDIR}/src/ucos/os_tmr.p1.d ${OBJECTDIR}/main.p1.d ${OBJECTDIR}/src/os_cpu_c.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/ucos/os_core.p1 ${OBJECTDIR}/src/ucos/os_sem.p1 ${OBJECTDIR}/src/ucos/os_flag.p1 ${OBJECTDIR}/src/ucos/os_time.p1 ${OBJECTDIR}/src/ucos/os_mem.p1 ${OBJECTDIR}/src/ucos/os_mbox.p1 ${OBJECTDIR}/src/ucos/os_q.p1 ${OBJECTDIR}/src/ucos/os_task.p1 ${OBJECTDIR}/src/ucos/os_dbg_r.p1 ${OBJECTDIR}/src/ucos/os_mutex.p1 ${OBJECTDIR}/src/ucos/ucos_ii.p1 ${OBJECTDIR}/src/ucos/os_tmr.p1 ${OBJECTDIR}/main.p1 ${OBJECTDIR}/src/os_cpu_c.p1

# Source Files
SOURCEFILES=src/ucos/os_core.c src/ucos/os_sem.c src/ucos/os_flag.c src/ucos/os_time.c src/ucos/os_mem.c src/ucos/os_mbox.c src/ucos/os_q.c src/ucos/os_task.c src/ucos/os_dbg_r.c src/ucos/os_mutex.c src/ucos/ucos_ii.c src/ucos/os_tmr.c main.c src/os_cpu_c.c


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K20
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/ucos/os_core.p1: src/ucos/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_core.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_core.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_core.p1  src/ucos/os_core.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_core.d ${OBJECTDIR}/src/ucos/os_core.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_core.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_sem.p1: src/ucos/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_sem.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_sem.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_sem.p1  src/ucos/os_sem.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_sem.d ${OBJECTDIR}/src/ucos/os_sem.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_sem.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_flag.p1: src/ucos/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_flag.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_flag.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_flag.p1  src/ucos/os_flag.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_flag.d ${OBJECTDIR}/src/ucos/os_flag.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_flag.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_time.p1: src/ucos/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_time.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_time.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_time.p1  src/ucos/os_time.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_time.d ${OBJECTDIR}/src/ucos/os_time.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_time.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_mem.p1: src/ucos/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_mem.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_mem.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_mem.p1  src/ucos/os_mem.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_mem.d ${OBJECTDIR}/src/ucos/os_mem.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_mem.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_mbox.p1: src/ucos/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_mbox.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_mbox.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_mbox.p1  src/ucos/os_mbox.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_mbox.d ${OBJECTDIR}/src/ucos/os_mbox.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_mbox.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_q.p1: src/ucos/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_q.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_q.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_q.p1  src/ucos/os_q.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_q.d ${OBJECTDIR}/src/ucos/os_q.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_q.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_task.p1: src/ucos/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_task.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_task.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_task.p1  src/ucos/os_task.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_task.d ${OBJECTDIR}/src/ucos/os_task.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_task.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_dbg_r.p1: src/ucos/os_dbg_r.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_dbg_r.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_dbg_r.p1  src/ucos/os_dbg_r.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_dbg_r.d ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_mutex.p1: src/ucos/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_mutex.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_mutex.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_mutex.p1  src/ucos/os_mutex.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_mutex.d ${OBJECTDIR}/src/ucos/os_mutex.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_mutex.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/ucos_ii.p1: src/ucos/ucos_ii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/ucos_ii.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/ucos_ii.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/ucos_ii.p1  src/ucos/ucos_ii.c 
	@-${MV} ${OBJECTDIR}/src/ucos/ucos_ii.d ${OBJECTDIR}/src/ucos/ucos_ii.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/ucos_ii.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_tmr.p1: src/ucos/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_tmr.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_tmr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_tmr.p1  src/ucos/os_tmr.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_tmr.d ${OBJECTDIR}/src/ucos/os_tmr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_tmr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/os_cpu_c.p1: src/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/os_cpu_c.p1.d 
	@${RM} ${OBJECTDIR}/src/os_cpu_c.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/os_cpu_c.p1  src/os_cpu_c.c 
	@-${MV} ${OBJECTDIR}/src/os_cpu_c.d ${OBJECTDIR}/src/os_cpu_c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/os_cpu_c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/ucos/os_core.p1: src/ucos/os_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_core.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_core.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_core.p1  src/ucos/os_core.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_core.d ${OBJECTDIR}/src/ucos/os_core.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_core.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_sem.p1: src/ucos/os_sem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_sem.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_sem.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_sem.p1  src/ucos/os_sem.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_sem.d ${OBJECTDIR}/src/ucos/os_sem.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_sem.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_flag.p1: src/ucos/os_flag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_flag.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_flag.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_flag.p1  src/ucos/os_flag.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_flag.d ${OBJECTDIR}/src/ucos/os_flag.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_flag.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_time.p1: src/ucos/os_time.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_time.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_time.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_time.p1  src/ucos/os_time.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_time.d ${OBJECTDIR}/src/ucos/os_time.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_time.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_mem.p1: src/ucos/os_mem.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_mem.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_mem.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_mem.p1  src/ucos/os_mem.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_mem.d ${OBJECTDIR}/src/ucos/os_mem.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_mem.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_mbox.p1: src/ucos/os_mbox.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_mbox.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_mbox.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_mbox.p1  src/ucos/os_mbox.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_mbox.d ${OBJECTDIR}/src/ucos/os_mbox.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_mbox.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_q.p1: src/ucos/os_q.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_q.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_q.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_q.p1  src/ucos/os_q.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_q.d ${OBJECTDIR}/src/ucos/os_q.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_q.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_task.p1: src/ucos/os_task.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_task.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_task.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_task.p1  src/ucos/os_task.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_task.d ${OBJECTDIR}/src/ucos/os_task.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_task.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_dbg_r.p1: src/ucos/os_dbg_r.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_dbg_r.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_dbg_r.p1  src/ucos/os_dbg_r.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_dbg_r.d ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_dbg_r.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_mutex.p1: src/ucos/os_mutex.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_mutex.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_mutex.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_mutex.p1  src/ucos/os_mutex.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_mutex.d ${OBJECTDIR}/src/ucos/os_mutex.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_mutex.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/ucos_ii.p1: src/ucos/ucos_ii.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/ucos_ii.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/ucos_ii.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/ucos_ii.p1  src/ucos/ucos_ii.c 
	@-${MV} ${OBJECTDIR}/src/ucos/ucos_ii.d ${OBJECTDIR}/src/ucos/ucos_ii.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/ucos_ii.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ucos/os_tmr.p1: src/ucos/os_tmr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src/ucos 
	@${RM} ${OBJECTDIR}/src/ucos/os_tmr.p1.d 
	@${RM} ${OBJECTDIR}/src/ucos/os_tmr.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ucos/os_tmr.p1  src/ucos/os_tmr.c 
	@-${MV} ${OBJECTDIR}/src/ucos/os_tmr.d ${OBJECTDIR}/src/ucos/os_tmr.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ucos/os_tmr.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/main.p1: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.p1.d 
	@${RM} ${OBJECTDIR}/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/main.p1  main.c 
	@-${MV} ${OBJECTDIR}/main.d ${OBJECTDIR}/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/os_cpu_c.p1: src/os_cpu_c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR}/src 
	@${RM} ${OBJECTDIR}/src/os_cpu_c.p1.d 
	@${RM} ${OBJECTDIR}/src/os_cpu_c.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/os_cpu_c.p1  src/os_cpu_c.c 
	@-${MV} ${OBJECTDIR}/src/os_cpu_c.d ${OBJECTDIR}/src/os_cpu_c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/os_cpu_c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=pickit3  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     --rom=default,-fd30-ffff --ram=default,-ef4-eff,-f9c-f9c,-fd4-fd4,-fdb-fdf,-fe3-fe7,-feb-fef,-ffd-fff  -odist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,-speed,+space,-debug --addrqual=ignore --mode=free -P -N255 -I"src" -I"src/ucos" --warn=0 --asmlist --summary=default,-psect,-class,+mem,-hex,-file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=-mcof,+elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"     -odist/${CND_CONF}/${IMAGE_TYPE}/test.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
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
