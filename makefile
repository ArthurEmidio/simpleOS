INCLUDE_DIR=./src
BIN_DIR=./bin
SRC_DIR=./src

#on debug mode use: make DEBUG=-g
DEBUG?=
CC=g++
CFLAGS=-std=c++11 $(DEBUG)

LINKER=g++ -c
LFLAGS=-std=c++11 -I$(INCLUDE_DIR) $(DEBUG)

SOURCES=$(wildcard $(SRC_DIR)/*.cpp)
INCLUDES=$(wildcard $(INCLUDE_DIR)/*.hpp)
OBJS=$(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
TARGET=simpleOS


$(BIN_DIR)/$(TARGET):$(OBJS)
	$(CC)  $(CFLAGS)  $^ -o $@;cp $(BIN_DIR)/$(TARGET) .

$(BIN_DIR)/%.o:$(SRC_DIR)/%.cpp
	$(CC) $(LFLAGS)  $< -c  -o $@

clean:
	rm $(BIN_DIR)/*.o $(BIN_DIR)/$(TARGET) $(TARGET)


