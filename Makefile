CC = gcc
SRC = ./src
BUILD = ./build
LIB = ./lib
TARGET = main
CFLAGS = -Wall -std=c2x


$(TARGET) :
	$(CC) $(CFLAGS) -o $(BUILD)/main $(SRC)/main.c $(LIB)/libserial/libserial.c

run :
	./build/main

clean :
	rm ./build/main