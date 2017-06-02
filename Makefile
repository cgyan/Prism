# =============================================================================================
# Makefile
# makefile should be in the project root directory
# =============================================================================================
CC 					:= g++
PROJDIR				:= $(shell pwd)
SRCDIR 				:= src
BUILDDIR			:= build
BINDIR				:= bin
TARGET				:= $(BINDIR)/prism
SRCEXT 				:= cpp
RECURSIVEWILDCARD 	= $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call RECURSIVEWILDCARD,$d/,$2))
ALLSRCS				:= $(call RECURSIVEWILDCARD,$(SRCDIR)/,*.$(SRCEXT))
EXCLDSRCS			:= src/eventsystem/Win32EventQueue.cpp
FILTSRCS			:= $(filter-out $(EXCLDSRCS),$(ALLSRCS))
OBJS				:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(FILTSRCS:.$(SRCEXT)=.o))
LIBDIR				:= -L. -L c:\libs
LIBS				:=
CPPFLAGS			:= -Wall
CFLAGS				:=
CXXFLAGS			:= -std=c++11
INC					:= -I inc -I c:\inc
DEFINES				:= # -D

# =============================================================================================

$(shell mkdir -p $(BUILDDIR))
$(shell mkdir -p $(BINDIR))

default : $(TARGET)

$(TARGET) : $(OBJS)
	@echo Building target: $@
	$(CC) $(OBJS) -o $(TARGET) $(LIBDIR) $(LIBS)
	@echo Finished building target: $@
	@echo ''

dll : $(OBJS)
	@echo Building DLL: $(TARGET).dll
	$(CC) -shared -o $(TARGET).dll $(OBJS) $(LIBDIR) $(LIBS) $(DEFINES)
	@echo Finished building DLL: $(TARGET).dll
	@echo ''

$(BUILDDIR)/%.o : $(SRCDIR)/%.cpp
	@echo Building file: $< into target: $@
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(CXXFLAGS) $(INC) $(DEFINES) -MD -c $< -o $@
	@cp $(BUILDDIR)/$*.d $(BUILDDIR)/$*.P
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' -e '/^$$/ d' -e 's/$$/ :/' < $(BUILDDIR)/$*.d >> $(BUILDDIR)/$*.P;
	@rm -f $(BUILDDIR)/$*.d
	@echo Finished building file: $<
	@echo ''

clean :
	rm -rf build bin/*

dump :
	@echo CC: 			$(CC)
	@echo PROJDIR:		$(PROJDIR)
	@echo SRCDIR: 		$(SRCDIR)
	@echo BUILDDIR: 	$(BUILDDIR)
	@echo BINDIR:	 	$(BINDIR)
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

-include $(BUILDDIR)/*.P
