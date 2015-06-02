CC = gcc

PROGRAMS= counter  show_shmat

all: $(PROGRAMS)

counter: counter.c
	$(CC) -Wall -o $@ $^

show_shmat: show_shmat.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
