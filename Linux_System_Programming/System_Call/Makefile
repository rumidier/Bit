CC = gcc

PROGRAMS = error creat lseek open read write read_02 dup write_1 write_2

all: $(PROGRAMS)

error: error.c
	$(CC) -Wall -o $@ $^

creat: creat.c
	$(CC) -Wall -o $@ $^

lseek: lseek.c
	$(CC) -Wall -o $@ $^

open: open.c
	$(CC) -Wall -o $@ $^

read: read.c
	$(CC) -Wall -o $@ $^

read_02: read_02.c
	$(CC) -Wall -o $@ $^

write: write.c
	$(CC) -Wall -o $@ $^

write_1: write_1.c
	$(CC) -Wall -o $@ $^

write_2: write_2.c
	$(CC) -Wall -o $@ $^

dup:
	$(CC) -Wall dup_1.c dup_2.c -o dup

clean:
	rm -rf $(PROGRAMS)
