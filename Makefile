CC = gcc
SRC = ./src
BUILD = ./build
LIB = ./lib
TARGET = main
CFLAGS = -Wall -Wextra -std=c2x

$(TARGET) :
	$(CC) $(CFLAGS) -o $(BUILD)/main $(SRC)/main.c $(LIB)/libserial/libserial.c

clean :
	rm ./build/main