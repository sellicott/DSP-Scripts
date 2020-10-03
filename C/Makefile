.PHONY: all clean

SRCS := plot-test.c gnuplotlib.c
INCLUDES := include

# source transformation
INCLUDES_ARG = $(INCLUDES:%=-I%)
OBJS := $(SRCS:%.c=%.o)
BIN_OBJS := $(OBJS:%.o=bin/%.o)

CC := gcc
CFLAGS := \
    -std=c99 -pedantic -Wall \
    -Wno-missing-braces -Wextra -Wno-missing-field-initializers -Wformat=2 \
    -Wswitch-default -Wswitch-enum -Wcast-align -Wpointer-arith \
    -Wbad-function-cast -Wstrict-overflow=5 -Winline \
    -Wundef -Wcast-qual -Wshadow -Wunreachable-code \
    -Wlogical-op -Wfloat-equal -Wredundant-decls \
    -Wold-style-definition \
    -ggdb3 \
    -O0 \
    -fno-omit-frame-pointer -ffloat-store -fno-common -fstrict-aliasing 

LDFLAGS := -lm

all: bin plot-test $(SRCS)

plot-test: $(BIN_OBJS)
	$(CC) $(CFLAGS) $^ ${LDFLAGS} -o $@

clean:
	rm -r bin
	rm plot-test 

bin/%.o %.c:
	$(CC) $(CFLAGS) $(INCLUDES_ARG) $*.c -c -o $@

# create a bin directory if it doesn't exist
bin:
	mkdir bin