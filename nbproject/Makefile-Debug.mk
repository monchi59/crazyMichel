#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/AsyncState.o \
	${OBJECTDIR}/CCRTPPacket.o \
	${OBJECTDIR}/CCrazyRadio.o \
	${OBJECTDIR}/CCrazyflie.o \
	${OBJECTDIR}/CTOC.o \
	${OBJECTDIR}/CrazyContainer.o \
	${OBJECTDIR}/FLContainer.o \
	${OBJECTDIR}/MyWindow.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-std=gnu++0x -fpermissive
CXXFLAGS=-std=gnu++0x -fpermissive

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs libusb-1.0` -lfltk -lfltk_forms -lfltk_gl -lfltk_images -lfltk_jpeg -lfltk_png -lfltk_z -ldl -lm -lXext -lX11 -std=c++0x `pkg-config --libs libxml-2.0`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazyyyisen

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazyyyisen: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazyyyisen ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/AsyncState.o: AsyncState.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/AsyncState.o AsyncState.cpp

${OBJECTDIR}/CCRTPPacket.o: CCRTPPacket.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCRTPPacket.o CCRTPPacket.cpp

${OBJECTDIR}/CCrazyRadio.o: CCrazyRadio.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCrazyRadio.o CCrazyRadio.cpp

${OBJECTDIR}/CCrazyflie.o: CCrazyflie.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CCrazyflie.o CCrazyflie.cpp

${OBJECTDIR}/CTOC.o: CTOC.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CTOC.o CTOC.cpp

${OBJECTDIR}/CrazyContainer.o: CrazyContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/CrazyContainer.o CrazyContainer.cpp

${OBJECTDIR}/FLContainer.o: FLContainer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/FLContainer.o FLContainer.cpp

${OBJECTDIR}/MyWindow.o: MyWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/MyWindow.o MyWindow.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Ifltk-1.3.2/png -Ifltk-1.3.2 -Ifltk-1.3.2/jpeg -Ifltk-1.3.2/zlib `pkg-config --cflags libusb-1.0` `pkg-config --cflags libxml-2.0`   -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/crazyyyisen

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
