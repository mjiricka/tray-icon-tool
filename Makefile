
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

# -Wno-deprecated-declarations: Whole gtk_status_icon
#   is deprecated, but I want status icon!
FLAGS := -Wall \
   -Wno-deprecated-declarations \
   -std=c99 \
   `pkg-config --cflags --libs gtk+-3.0`

FLAGS_DEBUG := -DDEBUG -O0 -g
FLAGS_RELEASE := -O2 -s


debug: FLAGS += $(FLAGS_DEBUG)
release: FLAGS += $(FLAGS_RELEASE)


.DEFAULT_GOAL := error
.PHONY: error debug release all clean distclean


${OUTPUT_DIR}:
	mkdir ${OUTPUT_DIR}

${OUTPUT_DIR}/util: ${OBJECTS}
	gcc ${OBJECTS} -o ${OUTPUT_DIR}/util ${FLAGS}

%.o: %.c
	gcc -c -o $@ $< ${FLAGS}

clean:
	rm -f ${OUTPUT_DIR}/*
	find ${SOURCES_ROOT} -name '*.o' -exec rm -f \{\} \;

distclean: clean
	rmdir ${OUTPUT_DIR}

all: ${OUTPUT_DIR} ${OUTPUT_DIR}/util

debug: all

release: all

error:
	@echo "You must specify either target 'debug' or 'release'."


