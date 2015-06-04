CC = gcc

PROGRAMS = tcp_s tcp_c talk_server talk_client gethtml

all: $(PROGRAMS)

tcp_s: tcp_s.c
	$(CC) -Wall -o $@ $^

tcp_c: tcp_c.c
	$(CC) -Wall -o $@ $^

talk_server: talk_server.c
	$(CC) -Wall -o $@ $^

talk_client: talk_client.c
	$(CC) -Wall -o $@ $^

gethtml: gethtml.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
