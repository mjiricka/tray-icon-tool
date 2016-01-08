

SOURCES := \
   main.c \
   server.c \
   client.c \
   commons.c \
   gui.c \
   utils.c

OUTPUT_DIR := bin
SOURCES_ROOT := src/

OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))
OBJECTS := $(addprefix $(SOURCES_ROOT), $(OBJECTS))

PARAMS := `pkg-config --cflags --libs gtk+-3.0` -Wno-deprecated-declarations

.DEFAULT_GOAL := all
.PHONY: all clean


${OUTPUT_DIR}:
	mkdir ${OUTPUT_DIR}

${OUTPUT_DIR}/util: ${OBJECTS}
	gcc ${OBJECTS} -o ${OUTPUT_DIR}/util ${PARAMS}

%.o: %.c
	gcc -c -o $@ $< ${PARAMS}

clean:
	rm -rf ${OUTPUT_DIR}
	find ${SOURCES_ROOT} -name '*.o' -exec rm -f \{\} \;

all: ${OUTPUT_DIR} ${OUTPUT_DIR}/util

