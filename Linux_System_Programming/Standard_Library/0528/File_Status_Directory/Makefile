CC = gcc

PROGRAMS = link unlink remove rename symlink readlink utime getcwd

all: $(PROGRAMS)

link: link.c
	$(CC) -Wall -o $@ $^

unlink: unlink.c
	$(CC) -Wall -o $@ $^

remove: remove.c
	$(CC) -Wall -o $@ $^

rename: rename.c
	$(CC) -Wall -o $@ $^

symlink: symlink.c
	$(CC) -Wall -o $@ $^

readlink: readlink.c
	$(CC) -Wall -o $@ $^

utime: utime.c
	$(CC) -Wall -o $@ $^

getcwd: getcwd.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
