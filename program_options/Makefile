# --------------------------------------------------------------------
# Jeff Nye (c) 2023, see jnutils/LICENSE and jnutils/README.md
# --------------------------------------------------------------------
.PHONY: clean run

CPP = g++
# --------------------------------------------------------------
TARGET = bin/test
# --------------------------------------------------------------
ALL_SRC = $(wildcard src/*.cpp)
ALL_OBJ = $(subst src,obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d))
# --------------------------------------------------------------
MSG_INC = -I../msg/inc

DEP  = -MMD -MP
DEF  = -DVERSION='"0.1.2"'
INC  = -I./inc $(MSG_INC)
OPT  = -g
STD  = -std=c++2a
WARN = -Wall
LIBS = -lboost_program_options -lpthread

CFLAGS   = $(OPT) $(DEP) $(DEF) $(INC) $(WARN)
CPPFLAGS = $(CFLAGS) $(STD)
LDFLAGS  = 
# --------------------------------------------------------------
default: run
only: $(TARGET)
# --------------------------------------------------------------
obj/%.o: src/%.cpp
	-mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $< -o $@

$(TARGET):	$(ALL_OBJ)
	-mkdir -p bin
	$(CPP) $(LDFLAGS) $^ -o $@ $(LIBS)

OPTS = \
  --ini file.ini \
  --multi multi_a \
  --multi multi_b \
  --bool_flag \
  --plain 42 \
  --hidden_one 1 \
  --hidden_two 2 \
  --query_options \

#  positional_option

run:	$(TARGET)
	@echo " ---------------------------------------------"
	@-$(TARGET) --help
	@echo " ---------------------------------------------"
	@-$(TARGET) --version
	@echo " ---------------------------------------------"
	@$(TARGET) $(OPTS) pos_option
	@echo " ---------------------------------------------"
	@$(TARGET) $(OPTS) --positional_option explicit_pos_option
	@echo " ---------------------------------------------"

# Helpful to diplay values of variables, e.g. make help-DEP
help-%:
	@echo $* = $($*)

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*
