SRC=$(wildcard *.c)  # en commentaire, je ne suis pas un grand amateur
EXE=prog

CC=gcc
CFLAGS:=-Wall -Wextra -g  $(sdl2-config --cflags)

LDFLAGS:=-lSDL2 -lSDL2_image -lSDL2_ttf -lm

OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

all: $(OBJ) 
	$(CC) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.o

-include $(DEP)
