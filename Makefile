# Flags
CC = gcc
ARGS = -Wall -Wextra -O3 -lm -o raytrace
SOURCE = src/Main.c

all:
	$(CC) $(SOURCE) $(ARGS)

clean:
	rm raytrace
