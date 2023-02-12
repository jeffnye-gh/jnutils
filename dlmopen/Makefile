# ----------------------------------------------------------------------
#  This file is part of jnutils, made public 2023, (c) Jeff Nye.
#  See LICENSE in the root directory.
# ----------------------------------------------------------------------
.PHONY: clean run

CPP = g++
# --------------------------------------------------------------
TARGET = bin/test
# --------------------------------------------------------------
ALL_SRC = $(filter-out dlo.cpp, $(wildcard src/*.cpp))
ALL_OBJ = $(subst src,obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d))

SO_OBJ  = obj/dlo.o
SO_LIB  = lib/libdlo.so

ALL_DEP += obj/dlo.d
# --------------------------------------------------------------
MSG_INC = -I../msg/inc

DEP  = -MMD -MP
DEF  = -DVERSION='"0.x.x"'
INC  = -I./inc $(MSG_INC)
OPT  = -g
STD  = -std=c++2a
WARN = -Wall
LIBS = -ldl

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC) $(WARN) -fPIC
CPPFLAGS = $(CFLAGS) $(STD)
$(TARGET) : LDFLAGS = -fPIC
$(SO_LIB) : LDFLAGS = -fPIC -shared
# --------------------------------------------------------------
default: $(SO_LIB) run
#not really only, more like dont run
only: $(SO_LIB) $(TARGET)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET):	$(SO_LIB) $(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

$(SO_LIB):	$(SO_OBJ)
	-mkdir -p lib
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

run:	$(TARGET)
	$(TARGET)

# Helpful to diplay values of variables, e.g. make help-DEP
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/* lib/*
