CC = gcc

PROGRAMS= ansi bsd gethostbyaddr getsockname socket accept bind geethostname listen uname arpa connect gethostbyname inet_ntoa tt

all: $(PROGRAMS)

ansi: ansi.c
	$(CC) -Wall -o $@ $^
bsd: bsd.c
	$(CC) -Wall -o $@ $^
gethostbyaddr: gethostbyaddr.c
	$(CC) -Wall -o $@ $^
getsockname: getsockname.c
	$(CC) -Wall -o $@ $^
socket: socket.c
	$(CC) -Wall -o $@ $^
accept: accept.c
	$(CC) -Wall -o $@ $^
bind: bind.c
	$(CC) -Wall -o $@ $^
geethostname: geethostname.c
	$(CC) -Wall -o $@ $^
listen: listen.c
	$(CC) -Wall -o $@ $^
uname: uname.c
	$(CC) -Wall -o $@ $^
arpa: arpa.c
	$(CC) -Wall -o $@ $^
connect: connect.c
	$(CC) -Wall -o $@ $^
gethostbyname: gethostbyname.c
	$(CC) -Wall -o $@ $^
inet_ntoa: inet_ntoa.c
	$(CC) -Wall -o $@ $^
tt: tt.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
