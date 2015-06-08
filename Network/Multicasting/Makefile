#335p

CC = gcc

SRCS = $(wildcard *.c)

PROGRAMS = $(basename $(SRC))

all: $(PROGRAMS)

%: %.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
