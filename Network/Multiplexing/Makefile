CC = gcc

PROGRAMS = block nonblock poll poll_02 poll_03 timer

all: $(PROGRAMS)

block: block.c
	$(CC) -Wall -o $@ $^
nonblock: nonblock.c 
	$(CC) -Wall -o $@ $^
poll: poll.c
	$(CC) -Wall -o $@ $^
poll_02: poll_02.c
	$(CC) -Wall -o $@ $^
poll_03: poll_03.c
	$(CC) -Wall -o $@ $^
timer: timer.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
