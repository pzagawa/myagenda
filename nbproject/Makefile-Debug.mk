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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/notesView/NoteItemView.o \
	${OBJECTDIR}/src/monthView/MonthViewWeekDayRect.o \
	${OBJECTDIR}/src/ui/CustomInfoBar.o \
	${OBJECTDIR}/src/database/SqlFieldSet.o \
	${OBJECTDIR}/src/ui/AboutDialog.o \
	${OBJECTDIR}/src/database/SqlDatabase.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/ui/CustomLabel.o \
	${OBJECTDIR}/src/dataManager/NoteInfoSummary.o \
	${OBJECTDIR}/src/MyAgendaApp.o \
	${OBJECTDIR}/src/database/SqlValue.o \
	${OBJECTDIR}/src/dataManager/DataManager.o \
	${OBJECTDIR}/src/monthView/MonthView.o \
	${OBJECTDIR}/src/ui/NotificationManager.o \
	${OBJECTDIR}/src/ui/CustomSeparator.o \
	${OBJECTDIR}/src/dataManager/NoteInfoItem.o \
	${OBJECTDIR}/src/ui/EditNoteDialog.o \
	${OBJECTDIR}/src/Resources.o \
	${OBJECTDIR}/src/DateTimeValue.o \
	${OBJECTDIR}/src/ui/LauncherQuicklist.o \
	${OBJECTDIR}/src/database/SqlRecordSet.o \
	${OBJECTDIR}/src/dataManager/DataTypes.o \
	${OBJECTDIR}/src/ui/TitleButton.o \
	${OBJECTDIR}/src/database/SqlField.o \
	${OBJECTDIR}/src/database/SHA1.o \
	${OBJECTDIR}/src/database/SqlTable.o \
	${OBJECTDIR}/src/Utils.o \
	${OBJECTDIR}/src/ui/MainWindow.o \
	${OBJECTDIR}/src/database/sqlite3.o \
	${OBJECTDIR}/src/database/SqlRecord.o \
	${OBJECTDIR}/src/Exception.o \
	${OBJECTDIR}/src/notesView/NoteListView.o \
	${OBJECTDIR}/src/monthView/MonthViewDayData.o \
	${OBJECTDIR}/src/database/SqlCommon.o \
	${OBJECTDIR}/src/Preferences.o \
	${OBJECTDIR}/src/notesView/NoteItemData.o \
	${OBJECTDIR}/src/monthView/MonthViewDayRect.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=`pkg-config --libs gtkmm-3.0` `pkg-config --libs unity` `pkg-config --libs libnotify`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/myagenda

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/myagenda: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/myagenda ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/notesView/NoteItemView.o: src/notesView/NoteItemView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/notesView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/notesView/NoteItemView.o src/notesView/NoteItemView.cpp

${OBJECTDIR}/src/monthView/MonthViewWeekDayRect.o: src/monthView/MonthViewWeekDayRect.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monthView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/monthView/MonthViewWeekDayRect.o src/monthView/MonthViewWeekDayRect.cpp

${OBJECTDIR}/src/ui/CustomInfoBar.o: src/ui/CustomInfoBar.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/CustomInfoBar.o src/ui/CustomInfoBar.cpp

${OBJECTDIR}/src/database/SqlFieldSet.o: src/database/SqlFieldSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlFieldSet.o src/database/SqlFieldSet.cpp

${OBJECTDIR}/src/ui/AboutDialog.o: src/ui/AboutDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/AboutDialog.o src/ui/AboutDialog.cpp

${OBJECTDIR}/src/database/SqlDatabase.o: src/database/SqlDatabase.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlDatabase.o src/database/SqlDatabase.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/ui/CustomLabel.o: src/ui/CustomLabel.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/CustomLabel.o src/ui/CustomLabel.cpp

${OBJECTDIR}/src/dataManager/NoteInfoSummary.o: src/dataManager/NoteInfoSummary.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/dataManager
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/dataManager/NoteInfoSummary.o src/dataManager/NoteInfoSummary.cpp

${OBJECTDIR}/src/MyAgendaApp.o: src/MyAgendaApp.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/MyAgendaApp.o src/MyAgendaApp.cpp

${OBJECTDIR}/src/database/SqlValue.o: src/database/SqlValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlValue.o src/database/SqlValue.cpp

${OBJECTDIR}/src/dataManager/DataManager.o: src/dataManager/DataManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/dataManager
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/dataManager/DataManager.o src/dataManager/DataManager.cpp

${OBJECTDIR}/src/monthView/MonthView.o: src/monthView/MonthView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monthView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/monthView/MonthView.o src/monthView/MonthView.cpp

${OBJECTDIR}/src/ui/NotificationManager.o: src/ui/NotificationManager.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/NotificationManager.o src/ui/NotificationManager.cpp

${OBJECTDIR}/src/ui/CustomSeparator.o: src/ui/CustomSeparator.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/CustomSeparator.o src/ui/CustomSeparator.cpp

${OBJECTDIR}/src/dataManager/NoteInfoItem.o: src/dataManager/NoteInfoItem.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/dataManager
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/dataManager/NoteInfoItem.o src/dataManager/NoteInfoItem.cpp

${OBJECTDIR}/src/ui/EditNoteDialog.o: src/ui/EditNoteDialog.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/EditNoteDialog.o src/ui/EditNoteDialog.cpp

${OBJECTDIR}/src/Resources.o: src/Resources.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Resources.o src/Resources.cpp

${OBJECTDIR}/src/DateTimeValue.o: src/DateTimeValue.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/DateTimeValue.o src/DateTimeValue.cpp

${OBJECTDIR}/src/ui/LauncherQuicklist.o: src/ui/LauncherQuicklist.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/LauncherQuicklist.o src/ui/LauncherQuicklist.cpp

${OBJECTDIR}/src/database/SqlRecordSet.o: src/database/SqlRecordSet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlRecordSet.o src/database/SqlRecordSet.cpp

${OBJECTDIR}/src/dataManager/DataTypes.o: src/dataManager/DataTypes.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/dataManager
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/dataManager/DataTypes.o src/dataManager/DataTypes.cpp

${OBJECTDIR}/src/ui/TitleButton.o: src/ui/TitleButton.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/TitleButton.o src/ui/TitleButton.cpp

${OBJECTDIR}/src/database/SqlField.o: src/database/SqlField.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlField.o src/database/SqlField.cpp

${OBJECTDIR}/src/database/SHA1.o: src/database/SHA1.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SHA1.o src/database/SHA1.cpp

${OBJECTDIR}/src/database/SqlTable.o: src/database/SqlTable.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlTable.o src/database/SqlTable.cpp

${OBJECTDIR}/src/Utils.o: src/Utils.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Utils.o src/Utils.cpp

${OBJECTDIR}/src/ui/MainWindow.o: src/ui/MainWindow.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/ui
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ui/MainWindow.o src/ui/MainWindow.cpp

${OBJECTDIR}/src/database/sqlite3.o: src/database/sqlite3.c 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.c) -g `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/sqlite3.o src/database/sqlite3.c

${OBJECTDIR}/src/database/SqlRecord.o: src/database/SqlRecord.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlRecord.o src/database/SqlRecord.cpp

${OBJECTDIR}/src/Exception.o: src/Exception.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Exception.o src/Exception.cpp

${OBJECTDIR}/src/notesView/NoteListView.o: src/notesView/NoteListView.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/notesView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/notesView/NoteListView.o src/notesView/NoteListView.cpp

${OBJECTDIR}/src/monthView/MonthViewDayData.o: src/monthView/MonthViewDayData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monthView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/monthView/MonthViewDayData.o src/monthView/MonthViewDayData.cpp

${OBJECTDIR}/src/database/SqlCommon.o: src/database/SqlCommon.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/database
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/database/SqlCommon.o src/database/SqlCommon.cpp

${OBJECTDIR}/src/Preferences.o: src/Preferences.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Preferences.o src/Preferences.cpp

${OBJECTDIR}/src/notesView/NoteItemData.o: src/notesView/NoteItemData.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/notesView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/notesView/NoteItemData.o src/notesView/NoteItemData.cpp

${OBJECTDIR}/src/monthView/MonthViewDayRect.o: src/monthView/MonthViewDayRect.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/monthView
	${RM} $@.d
	$(COMPILE.cc) -O3 -DDEBUG -Isrc/database -Isrc/dataManager -Isrc/monthView -Isrc/notesView -Isrc/ui -Isrc `pkg-config --cflags gtkmm-3.0` `pkg-config --cflags unity` `pkg-config --cflags libnotify`    -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/monthView/MonthViewDayRect.o src/monthView/MonthViewDayRect.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/myagenda

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
