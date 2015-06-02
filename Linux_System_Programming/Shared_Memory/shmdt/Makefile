CC = gcc

PROGRAMS= counter  show_shmdt

all: $(PROGRAMS)

counter: counter.c
	$(CC) -Wall -o $@ $^

show_shmdt: show_shmdt.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
