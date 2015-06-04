CC = gcc

PROGRAMS = tcp_s tcp_c

all: $(PROGRAMS)

tcp_s: tcp_s.c
	$(CC) -Wall -o $@ $^

tcp_c: tcp_c.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
