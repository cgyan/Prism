# =============================================================================================
# Makefile
# makefile should be in the project root directory
# =============================================================================================
CC 					:= g++
PROJDIR				:= $(shell pwd)
SRCDIR 				:= src
BUILDDIR			:= build
BINDIR				:= bin
TARGETEXT			:= dll
TARGET				:= $(BINDIR)/prism
SRCEXT 				:= cpp
RECURSIVEDIRSEARCH 	= $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECURSIVEDIRSEARCH,$d/,$2))
ALLSRCS				:= $(call RECURSIVEDIRSEARCH,$(SRCDIR)/,*.$(SRCEXT))
EXCLDSRCS			:=
FILTSRCS			:= $(filter-out $(EXCLDSRCS),$(ALLSRCS))
OBJS				:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(FILTSRCS:.$(SRCEXT)=.o))
LIBDIR				:= -L. -L c:\libs
LIBS				:=
CPPFLAGS			:= -Wall
CFLAGS				:=
CXXFLAGS			:= -std=c++11
INC					:= -I inc -I c:\inc
DEFINES				:= # -D

default : shared

# =============================================================================================

$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(BINDIR))

# build an executable
$(TARGET) : $(OBJS)
	@echo Building target: $@
	$(CC) $(OBJS) -o $(TARGET) $(LIBDIR) $(LIBS)
	@echo Finished building target: $@
	@echo ''

# build a shared library
shared : $(OBJS)
	@echo Building $(TARGETEXT): $(TARGET).$(TARGETEXT)
	$(CC) -shared -o $(TARGET).$(TARGETEXT) $(OBJS) $(LIBDIR) $(LIBS) $(DEFINES)
	@echo Finished building $(TARGETEXT): $(TARGET).$(TARGETEXT)
	@echo ''

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo Building file: $< into target: $@
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $(INC) $(DEFINES) -MMD -c $< -o $@
	@cp $(BUILDDIR)/$*.d $(BUILDDIR)/$*.P
	@rm -f $(BUILDDIR)/$*.d
	@echo Finished building file: $<
	@echo ''

clean :
	rm -rf build bin/*

cleaner : clean
	rm -rf bin

dump :
	@echo CC: 			$(CC)
	@echo PROJDIR:		$(PROJDIR)
	@echo SRCDIR: 		$(SRCDIR)
	@echo BUILDDIR: 	$(BUILDDIR)
	@echo BINDIR:	 	$(BINDIR)
	@echo TARGETEXT:	$(TARGETEXT)
	@echo TARGET: 		$(TARGET)
	@echo SRCEXT: 		$(SRCEXT)
	@echo ALLSRCS: 		$(ALLSRCS)
	@echo EXCLDSRCS:	$(EXCLDSRCS)
	@echo FILTSRCS:		$(FILTSRCS)
	@echo OBJS: 		$(OBJS)
	@echo LIBDIR:		$(LIBDIR)
	@echo LIBS:			$(LIBS)
	@echo CPPFLAGS:		$(CPPFLAGS)
	@echo CXXFLAGS: 	$(CXXFLAGS)
	@echo INC: 			$(INC)

# scans each subdirectory from $(BUILDDIR) downwards looking for all *.P files
# then includes them in the makefile
ALLPFILES := $(call RECURSIVEDIRSEARCH,$(BUILDDIR)/,*.P)
-include $(ALLPFILES)
