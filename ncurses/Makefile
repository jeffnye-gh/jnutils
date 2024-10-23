# --------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) 2023-2024 Jeff Nye.
#  See LICENSE in the root directory.
# --------------------------------------------------------------------
.PHONY: default only clean run

CPP = g++
# --------------------------------------------------------------
TARGET = bin/ndbg
# --------------------------------------------------------------
ALL_SRC = $(wildcard src/*.cpp)
ALL_OBJ = $(subst src/,obj/,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d)
# --------------------------------------------------------------
DEP  = -MMD -MP
DEF  = -DSTRING_DEFINE="\"v0.1.0\""
INC  = -I./inc
OPT  = -g
STD  = -std=c++20
WARN = -Wall
LIBS = -lncurses

CFLAGS   = $(OPT) $(STD) $(DEP) $(DEF) $(INC) 
CPPFLAGS = $(CFLAGS) $(STD)
LDFLAGS  =
# --------------------------------------------------------------
default: only
only: $(TARGET)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET):	$(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

run:	$(TARGET)
	$(TARGET)

# Helpful to diplay values of variables, e.g. make help-DEP
# I first saw this in riscv-isa-sim makefile, useful documentation
# mechanism with low effort
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*
