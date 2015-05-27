CC = gcc

PROGRAMS = tmpfile_1 setbuf_1 fflush_1 vprintf_1

all: $(PROGRAMS)

tmpfile_1: tmpfile_1.c
	$(CC) -Wall -o $@ $^

setbuf_1: setbuf_1.c
	$(CC) -Wall -o $@ $^

fflush_1: fflush_1.c
	$(CC) -Wall -o $@ $^

vprintf_1: vprintf_1.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
