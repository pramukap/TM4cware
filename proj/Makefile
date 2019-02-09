#******************************************************************************
#
# Makefile - Rules for building the Project Zero Example.
#
# Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
# 
# Texas Instruments (TI) is supplying this software for use solely and
# exclusively on TI's microcontroller products. The software is owned by
# TI and/or its suppliers, and is protected under applicable copyright
# laws. You may not combine this software with "viral" open-source
# software in order to form a larger program.
# 
# THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
# NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
# NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
# CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
# DAMAGES, FOR ANY REASON WHATSOEVER.
# 
# This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
#
#******************************************************************************

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
#ROOT=../../../..
ROOT=../

#
# Include the common make definitions.
#
include ${ROOT}/makedefs

#
# Where to find source files that do not live in this directory.
#
#VPATH=../drivers
#VPATH+=../../../../utils
VPATH=../drivers
VPATH+=../utils

#
# Where to find header files that do not live in the source directory.
#
#IPATH=..
#IPATH+=../../../..
IPATH=../
IPATH+=../

#
# Main C filename
#
MAIN=main

#
# The default rule, which causes the Project Zero Example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/${MAIN}.axf

#
# Enable debug code at compile-time
#
debug: CFLAGSgcc+=-DDEBUG
debug: CFLAGSgcc+=-g
debug: all

#
# Enable gdb debugging
# 
gdb: debug
	openocd --file /usr/share/openocd/scripts/board/ek-tm4c123gxl.cfg &
	arm-none-eabi-gdb -tui -command=init.gdb gcc/${MAIN}.axf

#
# The rule to flash the program to the chip.
#
flash:
	lm4flash gcc/${MAIN}.bin

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the Project Zero Example.
#
${COMPILER}/${MAIN}.axf: ${COMPILER}/${MAIN}.o
${COMPILER}/${MAIN}.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/${MAIN}.axf: ${ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/${MAIN}.axf: link.ld
SCATTERgcc_${MAIN}=link.ld
ENTRY_${MAIN}=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Rules for building custom drivers.
# ${COMPILER}/${MAIN}.axf: ${COMPILER}/[replace this with name of driver].o
#

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif

