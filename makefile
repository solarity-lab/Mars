CC = gcc

CFLAGS  = -g -O0
LDFLAGS =

SRC = $(wildcard *.c frontend/*.c backend/*.c)
OBJ = $(SRC:.c=.o)

TARGET = mars

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	cmd /c del /Q *.o frontend\*.o backend\*.o 2>nul || exit 0