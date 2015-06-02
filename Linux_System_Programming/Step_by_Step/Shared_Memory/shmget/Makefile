CC = gcc

PROGRAMS= counter  show_counter

all: $(PROGRAMS)

counter: counter.c
	$(CC) -Wall -o $@ $^
show_counter: show_counter.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
