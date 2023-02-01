.PHONY: only default clean server client mshtcp
include ../Vars.mk
# -----------------------------------------------------------------------
# -----------------------------------------------------------------------
MSHELL_VERSION=0.1.0

BOOST_INC = -I/usr/include/boost
BOOST_LIB = -L/usr/lib64

MSG_INC = -I../msg/inc
MSG_HDR = ../msg/inc/msg.h

TCP_INC  = -I../mshtcp/inc

ALL_SRC = $(wildcard src/*.cpp)
ALL_INC = $(wildcard inc/*.h)
SERVER_OBJ = $(subst src/,obj/server/,$(ALL_SRC:.cpp=.o))
CLIENT_OBJ = $(subst src/,obj/client/,$(ALL_SRC:.cpp=.o))
ALL_OBJ = $(SERVER_OBJ) $(CLIENT_OBJ)
ALL_DEP = $(ALL_OBJ:.o=.d)

NOT = obj/server/main.o obj/server/mstest.o \
      obj/client/main.o obj/server/client.o 
SERVER_LIB_OBJ  = $(filter-out $(NOT),$(SERVER_OBJ))
CLIENT_LIB_OBJ  = $(filter-out $(NOT),$(CLIENT_OBJ))
# -----------------------------------------------------------------------
#LIB_TARGET = ./lib/libmshell.a

SERVER_TARGET = ./bin/mshell_server_test
CLIENT_TARGET = ./bin/mshell_client_test

# These are inputs
MFM_SERVER_LIB = ../mshtcp/lib/mshserver.a
MFM_CLIENT_LIB = ../mshtcp/lib/mshclient.a

# These are outputs
SERVER_LIB = ./lib/libmshell_server.a
CLIENT_LIB = ./lib/libmshell_client.a

# -----------------------------------------------------------------------
WARN  = -Wall
INC   = -I./inc $(MSG_INC) $(TCP_INC) $(BOOST_INC)

CMN_CPPFLAGS = $(OPT) $(WARN) $(DEF) -MD -MP $(STD)

$(SERVER_TARGET): CPPFLAGS = $(CMN_CPPFLAGS) -DMSHELL_SERVER=1
$(CLIENT_TARGET): CPPFLAGS = $(CMN_CPPFLAGS) -DMSHELL_CLIENT=1

$(SERVER_TARGET): LIBS  = $(MFM_SERVER_LIB) -lpthread
$(CLIENT_TARGET): LIBS  = $(MFM_CLIENT_LIB) -lpthread

LDFLAGS  = $(STATIC)
ARFLAGS  = cqs 
# -----------------------------------------------------------------------
default: mshtcp server client
#	$(MAKE) -j18 server
#	$(MAKE) -j18 client

only: default

mshtcp:
	$(MAKE) -C ../mshtcp
server: $(SERVER_TARGET) $(SERVER_LIB)
client: $(CLIENT_TARGET) $(CLIENT_LIB)
# -----------------------------------------------------------------------
obj/client/%.o: src/%.cpp
	@mkdir -p obj/client;
	$(CPP) -c $(CPPFLAGS) $(INC) -o $@ $< 

obj/server/%.o: src/%.cpp
	@mkdir -p obj/server;
	$(CPP) -c $(CPPFLAGS) $(INC) -o $@ $< 

# -----------------------------------------------------------------------
$(SERVER_TARGET): $(SERVER_OBJ) 
	@mkdir -p bin;
	$(CPP) $(LDFLAGS) -o $@ $^ $(LIBS)

$(CLIENT_TARGET): $(CLIENT_OBJ) 
	@mkdir -p bin;
	$(CPP) $(LDFLAGS) -o $@ $^ $(LIBS)

# -----------------------------------------------------------------------
$(SERVER_LIB): $(SERVER_LIB_OBJ)
	@mkdir -p lib;
	$(AR) $(ARFLAGS) $@ $^ 

$(CLIENT_LIB): $(CLIENT_LIB_OBJ)
	@mkdir -p lib;
	$(AR) $(ARFLAGS) $@ $^ 

run: $(TST_TARGET)
	$(TST_TARGET)
# -----------------------------------------------------------------------
-include $(ALL_DEP)
# -----------------------------------------------------------------------
#clean_obj:
#	-rm -f obj/*
clean: 
	-rm -f lib/* bin/*
	-rm -rf obj/*
