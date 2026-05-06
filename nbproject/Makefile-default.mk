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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/main.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/main.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=sources/settings.c sources/datos_venta.c sources/dispatcher.c sources/config_model.c sources/eeprom_hw.c sources/checksum.c sources/global.c sources/credit.c sources/program.c sources/saldo.c sources/timers.c sources/uart.c sources/utils.c sources/vend.c sources/ui.c sources/ui_config.c sources/app.c sources/buttons.c sources/eeprom.c sources/lcd_hal.c sources/lcd_render.c sources/mdb_core.c sources/mdb_link.c sources/mdb_status.c sources/uart_hal.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/sources/settings.p1 ${OBJECTDIR}/sources/datos_venta.p1 ${OBJECTDIR}/sources/dispatcher.p1 ${OBJECTDIR}/sources/config_model.p1 ${OBJECTDIR}/sources/eeprom_hw.p1 ${OBJECTDIR}/sources/checksum.p1 ${OBJECTDIR}/sources/global.p1 ${OBJECTDIR}/sources/credit.p1 ${OBJECTDIR}/sources/program.p1 ${OBJECTDIR}/sources/saldo.p1 ${OBJECTDIR}/sources/timers.p1 ${OBJECTDIR}/sources/uart.p1 ${OBJECTDIR}/sources/utils.p1 ${OBJECTDIR}/sources/vend.p1 ${OBJECTDIR}/sources/ui.p1 ${OBJECTDIR}/sources/ui_config.p1 ${OBJECTDIR}/sources/app.p1 ${OBJECTDIR}/sources/buttons.p1 ${OBJECTDIR}/sources/eeprom.p1 ${OBJECTDIR}/sources/lcd_hal.p1 ${OBJECTDIR}/sources/lcd_render.p1 ${OBJECTDIR}/sources/mdb_core.p1 ${OBJECTDIR}/sources/mdb_link.p1 ${OBJECTDIR}/sources/mdb_status.p1 ${OBJECTDIR}/sources/uart_hal.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/sources/settings.p1.d ${OBJECTDIR}/sources/datos_venta.p1.d ${OBJECTDIR}/sources/dispatcher.p1.d ${OBJECTDIR}/sources/config_model.p1.d ${OBJECTDIR}/sources/eeprom_hw.p1.d ${OBJECTDIR}/sources/checksum.p1.d ${OBJECTDIR}/sources/global.p1.d ${OBJECTDIR}/sources/credit.p1.d ${OBJECTDIR}/sources/program.p1.d ${OBJECTDIR}/sources/saldo.p1.d ${OBJECTDIR}/sources/timers.p1.d ${OBJECTDIR}/sources/uart.p1.d ${OBJECTDIR}/sources/utils.p1.d ${OBJECTDIR}/sources/vend.p1.d ${OBJECTDIR}/sources/ui.p1.d ${OBJECTDIR}/sources/ui_config.p1.d ${OBJECTDIR}/sources/app.p1.d ${OBJECTDIR}/sources/buttons.p1.d ${OBJECTDIR}/sources/eeprom.p1.d ${OBJECTDIR}/sources/lcd_hal.p1.d ${OBJECTDIR}/sources/lcd_render.p1.d ${OBJECTDIR}/sources/mdb_core.p1.d ${OBJECTDIR}/sources/mdb_link.p1.d ${OBJECTDIR}/sources/mdb_status.p1.d ${OBJECTDIR}/sources/uart_hal.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/sources/settings.p1 ${OBJECTDIR}/sources/datos_venta.p1 ${OBJECTDIR}/sources/dispatcher.p1 ${OBJECTDIR}/sources/config_model.p1 ${OBJECTDIR}/sources/eeprom_hw.p1 ${OBJECTDIR}/sources/checksum.p1 ${OBJECTDIR}/sources/global.p1 ${OBJECTDIR}/sources/credit.p1 ${OBJECTDIR}/sources/program.p1 ${OBJECTDIR}/sources/saldo.p1 ${OBJECTDIR}/sources/timers.p1 ${OBJECTDIR}/sources/uart.p1 ${OBJECTDIR}/sources/utils.p1 ${OBJECTDIR}/sources/vend.p1 ${OBJECTDIR}/sources/ui.p1 ${OBJECTDIR}/sources/ui_config.p1 ${OBJECTDIR}/sources/app.p1 ${OBJECTDIR}/sources/buttons.p1 ${OBJECTDIR}/sources/eeprom.p1 ${OBJECTDIR}/sources/lcd_hal.p1 ${OBJECTDIR}/sources/lcd_render.p1 ${OBJECTDIR}/sources/mdb_core.p1 ${OBJECTDIR}/sources/mdb_link.p1 ${OBJECTDIR}/sources/mdb_status.p1 ${OBJECTDIR}/sources/uart_hal.p1

# Source Files
SOURCEFILES=sources/settings.c sources/datos_venta.c sources/dispatcher.c sources/config_model.c sources/eeprom_hw.c sources/checksum.c sources/global.c sources/credit.c sources/program.c sources/saldo.c sources/timers.c sources/uart.c sources/utils.c sources/vend.c sources/ui.c sources/ui_config.c sources/app.c sources/buttons.c sources/eeprom.c sources/lcd_hal.c sources/lcd_render.c sources/mdb_core.c sources/mdb_link.c sources/mdb_status.c sources/uart_hal.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/main.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4550
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/sources/settings.p1: sources/settings.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/settings.p1.d 
	@${RM} ${OBJECTDIR}/sources/settings.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/settings.p1 sources/settings.c 
	@-${MV} ${OBJECTDIR}/sources/settings.d ${OBJECTDIR}/sources/settings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/settings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/datos_venta.p1: sources/datos_venta.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/datos_venta.p1.d 
	@${RM} ${OBJECTDIR}/sources/datos_venta.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/datos_venta.p1 sources/datos_venta.c 
	@-${MV} ${OBJECTDIR}/sources/datos_venta.d ${OBJECTDIR}/sources/datos_venta.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/datos_venta.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/dispatcher.p1: sources/dispatcher.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/dispatcher.p1.d 
	@${RM} ${OBJECTDIR}/sources/dispatcher.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/dispatcher.p1 sources/dispatcher.c 
	@-${MV} ${OBJECTDIR}/sources/dispatcher.d ${OBJECTDIR}/sources/dispatcher.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/dispatcher.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/config_model.p1: sources/config_model.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/config_model.p1.d 
	@${RM} ${OBJECTDIR}/sources/config_model.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/config_model.p1 sources/config_model.c 
	@-${MV} ${OBJECTDIR}/sources/config_model.d ${OBJECTDIR}/sources/config_model.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/config_model.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/eeprom_hw.p1: sources/eeprom_hw.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/eeprom_hw.p1.d 
	@${RM} ${OBJECTDIR}/sources/eeprom_hw.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/eeprom_hw.p1 sources/eeprom_hw.c 
	@-${MV} ${OBJECTDIR}/sources/eeprom_hw.d ${OBJECTDIR}/sources/eeprom_hw.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/eeprom_hw.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/checksum.p1: sources/checksum.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/checksum.p1.d 
	@${RM} ${OBJECTDIR}/sources/checksum.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/checksum.p1 sources/checksum.c 
	@-${MV} ${OBJECTDIR}/sources/checksum.d ${OBJECTDIR}/sources/checksum.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/checksum.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/global.p1: sources/global.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/global.p1.d 
	@${RM} ${OBJECTDIR}/sources/global.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/global.p1 sources/global.c 
	@-${MV} ${OBJECTDIR}/sources/global.d ${OBJECTDIR}/sources/global.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/global.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/credit.p1: sources/credit.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/credit.p1.d 
	@${RM} ${OBJECTDIR}/sources/credit.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/credit.p1 sources/credit.c 
	@-${MV} ${OBJECTDIR}/sources/credit.d ${OBJECTDIR}/sources/credit.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/credit.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/program.p1: sources/program.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/program.p1.d 
	@${RM} ${OBJECTDIR}/sources/program.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/program.p1 sources/program.c 
	@-${MV} ${OBJECTDIR}/sources/program.d ${OBJECTDIR}/sources/program.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/program.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/saldo.p1: sources/saldo.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/saldo.p1.d 
	@${RM} ${OBJECTDIR}/sources/saldo.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/saldo.p1 sources/saldo.c 
	@-${MV} ${OBJECTDIR}/sources/saldo.d ${OBJECTDIR}/sources/saldo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/saldo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/timers.p1: sources/timers.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/timers.p1.d 
	@${RM} ${OBJECTDIR}/sources/timers.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/timers.p1 sources/timers.c 
	@-${MV} ${OBJECTDIR}/sources/timers.d ${OBJECTDIR}/sources/timers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/timers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/uart.p1: sources/uart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/uart.p1.d 
	@${RM} ${OBJECTDIR}/sources/uart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/uart.p1 sources/uart.c 
	@-${MV} ${OBJECTDIR}/sources/uart.d ${OBJECTDIR}/sources/uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/utils.p1: sources/utils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/utils.p1.d 
	@${RM} ${OBJECTDIR}/sources/utils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/utils.p1 sources/utils.c 
	@-${MV} ${OBJECTDIR}/sources/utils.d ${OBJECTDIR}/sources/utils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/utils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/vend.p1: sources/vend.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/vend.p1.d 
	@${RM} ${OBJECTDIR}/sources/vend.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/vend.p1 sources/vend.c 
	@-${MV} ${OBJECTDIR}/sources/vend.d ${OBJECTDIR}/sources/vend.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/vend.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/ui.p1: sources/ui.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ui.p1.d 
	@${RM} ${OBJECTDIR}/sources/ui.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/ui.p1 sources/ui.c 
	@-${MV} ${OBJECTDIR}/sources/ui.d ${OBJECTDIR}/sources/ui.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/ui.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/ui_config.p1: sources/ui_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ui_config.p1.d 
	@${RM} ${OBJECTDIR}/sources/ui_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/ui_config.p1 sources/ui_config.c 
	@-${MV} ${OBJECTDIR}/sources/ui_config.d ${OBJECTDIR}/sources/ui_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/ui_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/app.p1: sources/app.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/app.p1.d 
	@${RM} ${OBJECTDIR}/sources/app.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/app.p1 sources/app.c 
	@-${MV} ${OBJECTDIR}/sources/app.d ${OBJECTDIR}/sources/app.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/app.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/buttons.p1: sources/buttons.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/buttons.p1.d 
	@${RM} ${OBJECTDIR}/sources/buttons.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/buttons.p1 sources/buttons.c 
	@-${MV} ${OBJECTDIR}/sources/buttons.d ${OBJECTDIR}/sources/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/eeprom.p1: sources/eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/sources/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/eeprom.p1 sources/eeprom.c 
	@-${MV} ${OBJECTDIR}/sources/eeprom.d ${OBJECTDIR}/sources/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/lcd_hal.p1: sources/lcd_hal.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/lcd_hal.p1.d 
	@${RM} ${OBJECTDIR}/sources/lcd_hal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/lcd_hal.p1 sources/lcd_hal.c 
	@-${MV} ${OBJECTDIR}/sources/lcd_hal.d ${OBJECTDIR}/sources/lcd_hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/lcd_hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/lcd_render.p1: sources/lcd_render.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/lcd_render.p1.d 
	@${RM} ${OBJECTDIR}/sources/lcd_render.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/lcd_render.p1 sources/lcd_render.c 
	@-${MV} ${OBJECTDIR}/sources/lcd_render.d ${OBJECTDIR}/sources/lcd_render.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/lcd_render.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/mdb_core.p1: sources/mdb_core.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/mdb_core.p1.d 
	@${RM} ${OBJECTDIR}/sources/mdb_core.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/mdb_core.p1 sources/mdb_core.c 
	@-${MV} ${OBJECTDIR}/sources/mdb_core.d ${OBJECTDIR}/sources/mdb_core.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/mdb_core.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/mdb_link.p1: sources/mdb_link.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/mdb_link.p1.d 
	@${RM} ${OBJECTDIR}/sources/mdb_link.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/mdb_link.p1 sources/mdb_link.c 
	@-${MV} ${OBJECTDIR}/sources/mdb_link.d ${OBJECTDIR}/sources/mdb_link.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/mdb_link.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/mdb_status.p1: sources/mdb_status.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/mdb_status.p1.d 
	@${RM} ${OBJECTDIR}/sources/mdb_status.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/mdb_status.p1 sources/mdb_status.c 
	@-${MV} ${OBJECTDIR}/sources/mdb_status.d ${OBJECTDIR}/sources/mdb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/mdb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/uart_hal.p1: sources/uart_hal.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/uart_hal.p1.d 
	@${RM} ${OBJECTDIR}/sources/uart_hal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/uart_hal.p1 sources/uart_hal.c 
	@-${MV} ${OBJECTDIR}/sources/uart_hal.d ${OBJECTDIR}/sources/uart_hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/uart_hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/sources/settings.p1: sources/settings.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/settings.p1.d 
	@${RM} ${OBJECTDIR}/sources/settings.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/settings.p1 sources/settings.c 
	@-${MV} ${OBJECTDIR}/sources/settings.d ${OBJECTDIR}/sources/settings.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/settings.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/datos_venta.p1: sources/datos_venta.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/datos_venta.p1.d 
	@${RM} ${OBJECTDIR}/sources/datos_venta.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/datos_venta.p1 sources/datos_venta.c 
	@-${MV} ${OBJECTDIR}/sources/datos_venta.d ${OBJECTDIR}/sources/datos_venta.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/datos_venta.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/dispatcher.p1: sources/dispatcher.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/dispatcher.p1.d 
	@${RM} ${OBJECTDIR}/sources/dispatcher.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/dispatcher.p1 sources/dispatcher.c 
	@-${MV} ${OBJECTDIR}/sources/dispatcher.d ${OBJECTDIR}/sources/dispatcher.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/dispatcher.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/config_model.p1: sources/config_model.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/config_model.p1.d 
	@${RM} ${OBJECTDIR}/sources/config_model.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/config_model.p1 sources/config_model.c 
	@-${MV} ${OBJECTDIR}/sources/config_model.d ${OBJECTDIR}/sources/config_model.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/config_model.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/eeprom_hw.p1: sources/eeprom_hw.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/eeprom_hw.p1.d 
	@${RM} ${OBJECTDIR}/sources/eeprom_hw.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/eeprom_hw.p1 sources/eeprom_hw.c 
	@-${MV} ${OBJECTDIR}/sources/eeprom_hw.d ${OBJECTDIR}/sources/eeprom_hw.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/eeprom_hw.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/checksum.p1: sources/checksum.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/checksum.p1.d 
	@${RM} ${OBJECTDIR}/sources/checksum.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/checksum.p1 sources/checksum.c 
	@-${MV} ${OBJECTDIR}/sources/checksum.d ${OBJECTDIR}/sources/checksum.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/checksum.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/global.p1: sources/global.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/global.p1.d 
	@${RM} ${OBJECTDIR}/sources/global.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/global.p1 sources/global.c 
	@-${MV} ${OBJECTDIR}/sources/global.d ${OBJECTDIR}/sources/global.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/global.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/credit.p1: sources/credit.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/credit.p1.d 
	@${RM} ${OBJECTDIR}/sources/credit.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/credit.p1 sources/credit.c 
	@-${MV} ${OBJECTDIR}/sources/credit.d ${OBJECTDIR}/sources/credit.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/credit.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/program.p1: sources/program.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/program.p1.d 
	@${RM} ${OBJECTDIR}/sources/program.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/program.p1 sources/program.c 
	@-${MV} ${OBJECTDIR}/sources/program.d ${OBJECTDIR}/sources/program.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/program.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/saldo.p1: sources/saldo.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/saldo.p1.d 
	@${RM} ${OBJECTDIR}/sources/saldo.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/saldo.p1 sources/saldo.c 
	@-${MV} ${OBJECTDIR}/sources/saldo.d ${OBJECTDIR}/sources/saldo.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/saldo.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/timers.p1: sources/timers.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/timers.p1.d 
	@${RM} ${OBJECTDIR}/sources/timers.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/timers.p1 sources/timers.c 
	@-${MV} ${OBJECTDIR}/sources/timers.d ${OBJECTDIR}/sources/timers.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/timers.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/uart.p1: sources/uart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/uart.p1.d 
	@${RM} ${OBJECTDIR}/sources/uart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/uart.p1 sources/uart.c 
	@-${MV} ${OBJECTDIR}/sources/uart.d ${OBJECTDIR}/sources/uart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/uart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/utils.p1: sources/utils.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/utils.p1.d 
	@${RM} ${OBJECTDIR}/sources/utils.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/utils.p1 sources/utils.c 
	@-${MV} ${OBJECTDIR}/sources/utils.d ${OBJECTDIR}/sources/utils.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/utils.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/vend.p1: sources/vend.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/vend.p1.d 
	@${RM} ${OBJECTDIR}/sources/vend.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/vend.p1 sources/vend.c 
	@-${MV} ${OBJECTDIR}/sources/vend.d ${OBJECTDIR}/sources/vend.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/vend.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/ui.p1: sources/ui.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ui.p1.d 
	@${RM} ${OBJECTDIR}/sources/ui.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/ui.p1 sources/ui.c 
	@-${MV} ${OBJECTDIR}/sources/ui.d ${OBJECTDIR}/sources/ui.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/ui.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/ui_config.p1: sources/ui_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/ui_config.p1.d 
	@${RM} ${OBJECTDIR}/sources/ui_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/ui_config.p1 sources/ui_config.c 
	@-${MV} ${OBJECTDIR}/sources/ui_config.d ${OBJECTDIR}/sources/ui_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/ui_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/app.p1: sources/app.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/app.p1.d 
	@${RM} ${OBJECTDIR}/sources/app.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/app.p1 sources/app.c 
	@-${MV} ${OBJECTDIR}/sources/app.d ${OBJECTDIR}/sources/app.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/app.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/buttons.p1: sources/buttons.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/buttons.p1.d 
	@${RM} ${OBJECTDIR}/sources/buttons.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/buttons.p1 sources/buttons.c 
	@-${MV} ${OBJECTDIR}/sources/buttons.d ${OBJECTDIR}/sources/buttons.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/buttons.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/eeprom.p1: sources/eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/eeprom.p1.d 
	@${RM} ${OBJECTDIR}/sources/eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/eeprom.p1 sources/eeprom.c 
	@-${MV} ${OBJECTDIR}/sources/eeprom.d ${OBJECTDIR}/sources/eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/lcd_hal.p1: sources/lcd_hal.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/lcd_hal.p1.d 
	@${RM} ${OBJECTDIR}/sources/lcd_hal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/lcd_hal.p1 sources/lcd_hal.c 
	@-${MV} ${OBJECTDIR}/sources/lcd_hal.d ${OBJECTDIR}/sources/lcd_hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/lcd_hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/lcd_render.p1: sources/lcd_render.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/lcd_render.p1.d 
	@${RM} ${OBJECTDIR}/sources/lcd_render.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/lcd_render.p1 sources/lcd_render.c 
	@-${MV} ${OBJECTDIR}/sources/lcd_render.d ${OBJECTDIR}/sources/lcd_render.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/lcd_render.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/mdb_core.p1: sources/mdb_core.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/mdb_core.p1.d 
	@${RM} ${OBJECTDIR}/sources/mdb_core.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/mdb_core.p1 sources/mdb_core.c 
	@-${MV} ${OBJECTDIR}/sources/mdb_core.d ${OBJECTDIR}/sources/mdb_core.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/mdb_core.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/mdb_link.p1: sources/mdb_link.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/mdb_link.p1.d 
	@${RM} ${OBJECTDIR}/sources/mdb_link.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/mdb_link.p1 sources/mdb_link.c 
	@-${MV} ${OBJECTDIR}/sources/mdb_link.d ${OBJECTDIR}/sources/mdb_link.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/mdb_link.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/mdb_status.p1: sources/mdb_status.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/mdb_status.p1.d 
	@${RM} ${OBJECTDIR}/sources/mdb_status.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/mdb_status.p1 sources/mdb_status.c 
	@-${MV} ${OBJECTDIR}/sources/mdb_status.d ${OBJECTDIR}/sources/mdb_status.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/mdb_status.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/sources/uart_hal.p1: sources/uart_hal.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/sources" 
	@${RM} ${OBJECTDIR}/sources/uart_hal.p1.d 
	@${RM} ${OBJECTDIR}/sources/uart_hal.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/sources/uart_hal.p1 sources/uart_hal.c 
	@-${MV} ${OBJECTDIR}/sources/uart_hal.d ${OBJECTDIR}/sources/uart_hal.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/sources/uart_hal.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/main.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/main.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/main.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/main.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/main.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/main.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -memi=wordwrite -O2 -fasmfile -Og -maddrqual=ignore -xassembler-with-cpp -I"Include" -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/main.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
