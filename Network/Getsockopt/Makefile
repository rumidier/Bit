# 283p~

CC = gcc

SRCS = $(wildcard *.c)

PROGRAMS = $(basename $(SRCS))

all: $(PROGRAMS)

%: %.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
