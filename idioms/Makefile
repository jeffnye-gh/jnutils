# --------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) Jeff Nye.
#  See LICENSE in the root directory.
# --------------------------------------------------------------------
.PHONY: clean run

CPP = g++
# --------------------------------------------------------------
TARGET = bin/mine
# --------------------------------------------------------------
ALL_SRC = $(wildcard src/*.cpp)
ALL_OBJ = $(subst src,obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d))
# --------------------------------------------------------------
BOOST_INC = -I/usr/local/boost

DEP  = -MMD -MP
DEF  = -DSTRING_DEFINE="\"v1.1.1\""
INC  = -I./inc -I../msg/inc $(BOOST_INC)
OPT  = -g
STD  = -std=c++2a
WARN = -Wall
LIBS =

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC)
CPPFLAGS = $(CFLAGS) $(STD)

# Target dependent variables
$(TARGET) : LDFLAGS = -fPIC
# --------------------------------------------------------------
default: run
only: $(TARGET)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET):  $(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

run:  $(TARGET)
	$(TARGET)

# Helpful to diplay values of variables, e.g. make help-DEP
# I first saw this in riscv-isa-sim makefile, useful documentation
# mechanism with low effort
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*

