CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(OBJ) $(TARGET).exe $(TARGET) 2>nul
else
	rm -f $(OBJ) $(TARGET)
endif
