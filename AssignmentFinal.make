CC = gcc
CFLAGS = -Wall -Wextra -O2
LDFLAGS =

SRC = AssignmentFinal.c
HDR = diloseis.h
OBJ = $(SRC:.c=.o)

TARGET = AssignmentFinal

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
.PHONY: all clean
