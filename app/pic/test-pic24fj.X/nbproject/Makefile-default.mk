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
SOURCEFILES_QUOTED_IF_SPACED=../../lib/frw/pic/frw_string.c src/main.c src/app_cfg.c ../../lib/frw/pic/drv/chip/pic24fj/drv_usart.c ../../lib/frw/pic/drv/drv_core.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/353607548/frw_string.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/app_cfg.o ${OBJECTDIR}/_ext/1912918919/drv_usart.o ${OBJECTDIR}/_ext/454452373/drv_core.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/353607548/frw_string.o.d ${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/src/app_cfg.o.d ${OBJECTDIR}/_ext/1912918919/drv_usart.o.d ${OBJECTDIR}/_ext/454452373/drv_core.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/353607548/frw_string.o ${OBJECTDIR}/src/main.o ${OBJECTDIR}/src/app_cfg.o ${OBJECTDIR}/_ext/1912918919/drv_usart.o ${OBJECTDIR}/_ext/454452373/drv_core.o

# Source Files
SOURCEFILES=../../lib/frw/pic/frw_string.c src/main.c src/app_cfg.c ../../lib/frw/pic/drv/chip/pic24fj/drv_usart.c ../../lib/frw/pic/drv/drv_core.c


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
${OBJECTDIR}/_ext/353607548/frw_string.o: ../../lib/frw/pic/frw_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/353607548" 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/frw_string.c  -o ${OBJECTDIR}/_ext/353607548/frw_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/353607548/frw_string.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/353607548/frw_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app_cfg.o: src/app_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/app_cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app_cfg.c  -o ${OBJECTDIR}/src/app_cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app_cfg.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app_cfg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1912918919/drv_usart.o: ../../lib/frw/pic/drv/chip/pic24fj/drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1912918919" 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_usart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/chip/pic24fj/drv_usart.c  -o ${OBJECTDIR}/_ext/1912918919/drv_usart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1912918919/drv_usart.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1912918919/drv_usart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/454452373/drv_core.o: ../../lib/frw/pic/drv/drv_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/454452373" 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/drv_core.c  -o ${OBJECTDIR}/_ext/454452373/drv_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/454452373/drv_core.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/454452373/drv_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/353607548/frw_string.o: ../../lib/frw/pic/frw_string.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/353607548" 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o.d 
	@${RM} ${OBJECTDIR}/_ext/353607548/frw_string.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/frw_string.c  -o ${OBJECTDIR}/_ext/353607548/frw_string.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/353607548/frw_string.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/353607548/frw_string.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/main.o: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/main.c  -o ${OBJECTDIR}/src/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/main.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/app_cfg.o: src/app_cfg.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/app_cfg.o.d 
	@${RM} ${OBJECTDIR}/src/app_cfg.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/app_cfg.c  -o ${OBJECTDIR}/src/app_cfg.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/app_cfg.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/src/app_cfg.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/1912918919/drv_usart.o: ../../lib/frw/pic/drv/chip/pic24fj/drv_usart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/1912918919" 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_usart.o.d 
	@${RM} ${OBJECTDIR}/_ext/1912918919/drv_usart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/chip/pic24fj/drv_usart.c  -o ${OBJECTDIR}/_ext/1912918919/drv_usart.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/1912918919/drv_usart.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/1912918919/drv_usart.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/454452373/drv_core.o: ../../lib/frw/pic/drv/drv_core.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/454452373" 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o.d 
	@${RM} ${OBJECTDIR}/_ext/454452373/drv_core.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  ../../lib/frw/pic/drv/drv_core.c  -o ${OBJECTDIR}/_ext/454452373/drv_core.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/454452373/drv_core.o.d"        -g -omf=coff -mlarge-code -mlarge-data -mlarge-scalar -O1 -I"src" -I"../../lib/frw/pic" -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/_ext/454452373/drv_core.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
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
