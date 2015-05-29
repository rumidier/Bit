CC = gcc

PROGRAMS = getpid fork_00 fork_01 fork_02 fork_03 vfork exit_01 exit_02 wait execl

all: $(PROGRAMS)

getpid: getpid.c
	$(CC) -Wall -o $@ $^

fork_00: fork_00.c
	$(CC) -Wall -o $@ $^

fork_01: fork_01.c
	$(CC) -Wall -o $@ $^

fork_02: fork_02.c
	$(CC) -Wall -o $@ $^

fork_03: fork_03.c
	$(CC) -Wall -o $@ $^

vfork: vfork.c
	$(CC) -Wall -o $@ $^

exit_01: exit_01.c
	$(CC) -Wall -o $@ $^

exit_02: exit_02.c
	$(CC) -Wall -o $@ $^

wait: wait.c
	$(CC) -Wall -o $@ $^

execl: execl.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
