CC = gcc

PROGRAMS = access lstat umask chmod

all: $(PROGRAMS)

access: access.c
	$(CC) -Wall -o $@ $^

lstat: lstat.c
	$(CC) -Wall -o $@ $^

umask: umask.c
	$(CC) -Wall -o $@ $^

chmod: chmod.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
