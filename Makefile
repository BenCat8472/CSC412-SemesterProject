#GNU C/C++ Compiler and linker
GCC = g++
LINK = g++

BIN_DIR = bin
SRC_DIR = src
INC_DIR = inc

INC    = -I$(INC_DIR)
FILES  = $(shell echo $(SRC_DIR)/*.cpp)
SOURCE = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/unittests.cpp, $(FILES))
OBJS   = $(subst $(SRC_DIR),$(BIN_DIR),$(SOURCE:.cpp=.o))

# Compiler flags
CXXFLAGS = -Wall -O3 -std=c++11

# Fill in special libraries needed here
LIBS = -lglut -lGL -lGLU -lpthread

.PHONY: clean realclean help

all: $(BIN_DIR) main

main: $(BIN_DIR)/main.o $(OBJS)
	$(LINK) $(CXXFLAGS) -o $@ $^ $(LIBS)

unittests: CXXFLAGS = -DDEBUG -g -std=c++11
unittests: $(BIN_DIR)/unittests.o $(OBJS)
	$(LINK) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(BIN_DIR)/%.o: $(BIN_DIR)
	$(GCC) $(CXXFLAGS) -c -o $@ $(subst $(BIN_DIR),$(SRC_DIR),$(@:.o=.cpp)) $(INC)

debug: CXXFLAGS = -DDEBUG -g -std=c++11
debug: all

clean:
	rm -rf $(BIN_DIR) core main unittests

realclean: clean
	rm -f main.tgz

tar: clean
	tar zcvf main.tgz $(SOURCE) $(INC_DIR)/*.h Makefile

help:
	@echo "	make all       - builds the main target"
	@echo "	make           - same as make all"
	@echo "	make unittests - builds the unittests target"
	@echo "	make debug     - make all with -g and -DDEBUG"
	@echo "	make clean     - remove bin/* core main unittests"
	@echo "	make realclean - remove bin/* core main unittests main.tgz"
	@echo "	make tar       - make a tarball of the Makefile and all .cpp and .h"
	@echo "	make help      - this message"

$(BIN_DIR):
	mkdir $(BIN_DIR)
