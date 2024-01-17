# Variables
CC = gcc
CFLAGS = -I. -Wall -Wextra -g
DEPS = $(wildcard include/*.h)
OBJ = $(patsubst src/%.c, obj/%.o, $(wildcard src/*.c)) obj/main.o
TARGET = main

# Targets
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

obj/main.o: main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f obj/*.o $(TARGET)

run:
	./$(TARGET)