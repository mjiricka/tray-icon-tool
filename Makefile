.DEFAULT_GOAL := all
OBJ := main.o server.o client.o commons.o gui.o
BINOBJ := $(addprefix bin/, $(OBJ))
PARAMS := `pkg-config --cflags --libs gtk+-3.0` -Wno-deprecated-declarations

.PHONY: all clean


bin:
	mkdir bin

bin/%.o: src/%.c
	gcc -c -o $@ $< ${PARAMS}

bin/util: ${BINOBJ}
	cd bin ; gcc ${OBJ} -o util ${PARAMS}

clean:
	rm -rf bin

all: bin bin/util

