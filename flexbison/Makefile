# ---------------------------------------------------------------------
.PHONY: default run only flexx bisonx
# ---------------------------------------------------------------------
#AKEN_INC = -I /home/jeff/Development/Nile/Prerelease/AkenApi/inc
# ---------------------------------------------------------------------
TARGET = bin/tr
# ---------------------------------------------------------------------
CPP      = g++
LEX      = flex
YACC     = bison -d -v
INC      = -I ./inc -I ./obj $(AKEN_INC) -I /usr/include 
CPPFLAGS = -g $(INC) -std=c++11
LIBS = -lstdc++
# ---------------------------------------------------------------------
PREFIX = asp
LEXER  = ./src/$(PREFIX).l
GRMMR  = ./src/$(PREFIX).y

#Order matters here
FLX_SRC = ./obj/$(PREFIX).tab.cpp ./obj/lex.$(PREFIX).cpp
FLX_OBJ = ./obj/$(PREFIX).tab.o   ./obj/lex.$(PREFIX).o
FLX_DEP = $(subst ./src,./obj,$(FLX_SRC:.cpp=.d))

ALL_SRC = $(wildcard ./src/*.cpp) $(FLX_SRC)
ALL_OBJ = $(FLX_OBJ) $(subst ./src,./obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(subst ./src,./obj,$(ALL_OBJ:.o=.d))
ALL_INC = $(wildcard ./inc/*.h)
# ---------------------------------------------------------------------
default: run
	@echo $(ALL_SRC)

only: $(TARGET)

./obj/%.o: ./src/%.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<

./obj/%.o: ./obj/%.cpp
	$(CPP) -c $(CPPFLAGS) -o $@ $<

$(TARGET):  $(ALL_OBJ)
	$(CC) $(CPPFLAGS) -o $@ $^ $(LIBS)

./obj/$(PREFIX).tab.hpp \
./obj/$(PREFIX).tab.cpp: ./src/$(PREFIX).y $(ALL_INC)
	@mkdir -p obj
	$(YACC) -p$(PREFIX) -v -d -o ./obj/$(PREFIX).tab.cpp $<

./obj/$(PREFIX).tab.o: ./obj/$(PREFIX).tab.cpp
	@mkdir -p obj
	$(CPP)  -c $(CPPFLAGS) $(INC) $< -o $@

./obj/lex.$(PREFIX).cpp:  ./src/$(PREFIX).l \
                          ./obj/$(PREFIX).tab.hpp
	@mkdir -p obj
	$(LEX) -P$(PREFIX) -o $@ $<

./obj/lex.$(PREFIX).o: obj/lex.$(PREFIX).cpp
	@mkdir -p obj
	$(CPP)  -c $(CPPFLAGS) $(INC) $< -o $@

#flexx:  ./obj/lex.$(PREFIX).cpp
#bisonx: ./obj/$(PREFIX).tab.cpp
#
#./obj/lex.$(PREFIX).cpp:  $(LEXER)
#	$(LEX) -o$@ -P$(PREFIX) $<
#
#./obj/$(PREFIX).tab.cpp:  $(GRMMR)
#	$(YACC) -p$(PREFIX) -o $@ $<

run: $(TARGET)
	$(TARGET)

# ----------------------------------------------------------------------
-include $(ALL_DEP)
# ----------------------------------------------------------------------
# ----------------------------------------------------------------------
clean:
	-rm -f obj/* bin/* 
