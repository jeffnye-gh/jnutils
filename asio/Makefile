# --------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
#  See LICENSE in the root directory.
# --------------------------------------------------------------------
.PHONY: default only clean

CPP = g++
# --------------------------------------------------------------
TARG_SERVER = bin/server
TARG_CLIENT = bin/client
# --------------------------------------------------------------
ALL_CMN_SRC = $(wildcard common/*.cpp)
ALL_CMN_OBJ = $(subst common/,obj/,$(ALL_CMN_SRC:.cpp=.o))

ALL_SRV_SRC = $(wildcard server/*.cpp)
ALL_SRV_OBJ = $(subst server/,obj/,$(ALL_SRV_SRC:.cpp=.o)) $(ALL_CMN_OBJ)

ALL_CLI_SRC = $(wildcard client/*.cpp)
ALL_CLI_OBJ = $(subst client/,obj/,$(ALL_CLI_SRC:.cpp=.o)) $(ALL_CMN_OBJ)
ALL_DEP = $(ALL_SRV_OBJ:.o=.d) $(ALL_CLI_OBJ:.o=.d)
# --------------------------------------------------------------
DEP  = -MMD -MP
DEF  = -DSTRING_DEFINE="\"v0.1.0\""
INC  = -I. -Icommon
OPT  = -g
STD  = -std=c++20
WARN = -Wall
LIBS = -lboost_system

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC) 
CPPFLAGS = $(CFLAGS) $(STD)

# Target dependent variables - not used
$(TARG_SERVER) : LDFLAGS =
$(TARG_CLIENT) : LDFLAGS = 
# --------------------------------------------------------------
default: only
only: $(TARG_SERVER) $(TARG_CLIENT)
# --------------------------------------------------------------
obj/%.o: common/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

obj/%.o: server/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

obj/%.o: client/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARG_SERVER):	$(ALL_SRV_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

$(TARG_CLIENT):	$(ALL_CLI_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

# Helpful to diplay values of variables, e.g. make help-DEP
# I first saw this in riscv-isa-sim makefile, useful documentation
# mechanism with low effort
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*
