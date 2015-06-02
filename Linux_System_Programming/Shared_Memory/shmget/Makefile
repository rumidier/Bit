CC = gcc

PROGRAMS= counter  show_shmget

all: $(PROGRAMS)

counter: counter.c
	$(CC) -Wall -o $@ $^
show_shmget: show_shmget.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
