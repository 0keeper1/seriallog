CC = gcc
SRC = ./src
BUILD = ./build
LIB = ./lib
TARGET = main
CFLAGS = -Wall -Wextra -std=c2x -Oz

$(TARGET) :
	mkdir -p build
	$(CC) $(CFLAGS) -o $(BUILD)/seriallog $(SRC)/**.c $(LIB)/*/**.c

clean :
	rm ./build/seriallog