# Flags
CC = gcc
ARGS = -Wall -Wextra -O3 -lm -o raytrace
SOURCE = src/Main.c

all: compile

compile:
	$(CC) $(SOURCE) $(ARGS)

debug: ARGS += -g

clean:
	rm raytrace
