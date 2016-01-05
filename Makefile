.DEFAULT_GOAL := all
OBJ := main.o server.o client.o commons.o
BINOBJ := $(addprefix bin/, $(OBJ))

.PHONY: all clean


bin:
	mkdir bin

bin/%.o: src/%.c
	gcc -c -o $@ $<

bin/util: ${BINOBJ}
	cd bin ; gcc ${OBJ} -o util

clean:
	rm -rf bin

all: bin bin/util

