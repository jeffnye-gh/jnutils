.PHONY: default clean run libs only
include ../Vars.mk
# -----------------------------------------------------------------------
S_SRC  = src/tcp_server.cpp src/server_example.cpp src/client.cpp
C_SRC  = src/tcp_client.cpp src/client_example.cpp 

S_OBJ  = $(subst src/,obj/,$(S_SRC:.cpp=.o))
C_OBJ  = $(subst src/,obj/,$(C_SRC:.cpp=.o))

NOT     = obj/server_example.o obj/client_example.o
SL_OBJ  = $(filter-out $(NOT),$(S_OBJ))
CL_OBJ  = $(filter-out $(NOT),$(C_OBJ))

ALL_INC  = $(wildcard inc/*.h) 
ALL_DEP  = $(S_OBJ:.o=.d) $(C_OBJ:.o=.d)

SERVER = bin/server
CLIENT = bin/client

SERVER_LIB = lib/mshserver.a
CLIENT_LIB = lib/mshclient.a

LIBS  = -pthread
WARN  = -Wall -Wno-unused-variable -Wno-unused-but-set-variable
DEF  += 

INC   = -I./inc

CPPFLAGS = $(OPT) $(WARN) $(DEF) -MD -MP $(STD)
LDFLAGS  = 
## -----------------------------------------------------------------------
#default: $(SERVER) $(CLIENT)
default: only
test: libs run
only: libs
# -----------------------------------------------------------------------
obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CPP) -c $(CPPFLAGS) $(INC) -o $@ $< 

$(SERVER) :	$(S_OBJ) 
	@mkdir -p bin
	$(CPP) $(LDFLAGS) -o $@ $^ $(LIBS)

$(CLIENT) :	$(C_OBJ) 
	@mkdir -p bin
	$(CPP) $(LDFLAGS) -o $@ $^ $(LIBS)

libs: $(SERVER_LIB) $(CLIENT_LIB)

$(SERVER_LIB):	$(SL_OBJ)
	@mkdir -p lib
	$(AR) $(ARFLAGS) $@ $^
 
$(CLIENT_LIB):	$(CL_OBJ)
	@mkdir -p lib
	$(AR) $(ARFLAGS) $@ $^
 
run: $(SERVER) $(CLIENT)
	$(SERVER) &
	sleep 1
	$(CLIENT)
# -----------------------------------------------------------------------
-include $(ALL_DEP)
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------
clean:
	rm -f  bin/* obj/* lib/*
