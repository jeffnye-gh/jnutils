.phony: run default clean diff

CFLAGS = -std=c++11 -I./inc -MMD -MP

ALL_SRC = $(wildcard src/*.cpp)
ALL_OBJ = $(subst src,obj,$(ALL_SRC:.cpp=.o))
ALL_DEP = $(ALL_OBJ:.o=.d)

TARGET   = bin/fixture
 
default: run
#default:
#	@echo $(ALL_SRC)

obj/%.o: src/%.cpp
	@mkdir -p obj
	g++ -c $(CFLAGS) $< -o $@

$(TARGET): $(ALL_OBJ)
	@mkdir -p bin
	g++ $(LDFLAGS) $^ -o $@

#	cd data; tar xf dhrystone_opt3.bare.hex.bz2
run:	$(TARGET)
	$(TARGET)

diff:
	@echo "Checking lp tables"
	-diff -q lp_tables.txt ../lp_tables.txt
	@echo "Checking tg tables"
	-diff -q tg_tables.txt ../tg_tables.txt

-include $(ALL_DEP)

clean:
	-rm -f obj/* bin/*
	-rm -f history.txt loop_pred_entries.txt lpred_trace.txt
	-rm -f history.txt lp_tables.txt lp_transactions.txt
	-rm -f history.txt tg_tables.txt tg_transactions.txt
