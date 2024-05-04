CC = gcc
SRC = ./src
BUILD = ./build
TARGET = main
CFLAGS = -Wall -std=c2x


$(TARGET) :
	$(CC) $(CFLAGS) -o $(BUILD)/main $(SRC)/main.c

run :
	./build/main

clean :
	rm ./build/main