CC = gcc

PROGRAMS= counter show_counter show_shmctl

all: $(PROGRAMS)

counter: counter.c
	$(CC) -Wall -o $@ $^

show_counter: show_counter.c
	$(CC) -Wall -o $@ $^

show_shmctl: show_shmctl.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
