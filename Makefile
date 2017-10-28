# Flags
CC = gcc
ARGS = -Wall -Wextra -O3 -lm -o raycast
SOURCE = src/Main.c

all: compile

compile:
	$(CC) $(SOURCE) $(ARGS)

debug: ARGS += -g

clean:
	rm raytrace
