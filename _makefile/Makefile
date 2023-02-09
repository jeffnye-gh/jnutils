# --------------------------------------------------------------------
# Jeff Nye (c) 2023
# --------------------------------------------------------------------
.PHONY: clean run

CPP = g++
# --------------------------------------------------------------
TARGET_A = bin/testa
TARGET_B = bin/testb
# --------------------------------------------------------------
ALL_SRC = $(wildcard src/*.cpp)
ALL_OBJ = $(subst src,obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d))
# --------------------------------------------------------------
DEP  = -MMD -MP
DEF  = 
INC  = -I./inc
OPT  = -g
STD  = -std=c++2a
WARN = -Wall
LIBS =

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC) 
CPPFLAGS = $(CFLAGS) $(STD)

# Target dependent variables
$(TARGET_A) : LDFLAGS = -fPIC
$(TARGET_B) : LDFLAGS = 
# --------------------------------------------------------------
default: run
only: $(TARGET_A) $(TARGET_B)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET_A):	$(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

$(TARGET_B):	$(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

run:	$(TARGET_A) $(TARGET_B)
	$(TARGET_A)
	$(TARGET_B)

# Helpful to diplay values of variables, e.g. make help-DEP
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*
