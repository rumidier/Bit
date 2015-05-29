CC = gcc

PROGRAMS = fork_00 fork_01 fork_02 sys_ls wait execl newpgm execv execve exe_ls exe_test exe_test_02

all: $(PROGRAMS)

fork_00: fork_00.c
	$(CC) -Wall -o $@ $^

fork_01: fork_01.c
	$(CC) -Wall -o $@ $^

fork_02: fork_02.c
	$(CC) -Wall -o $@ $^

sys_ls: sys_ls.c
	$(CC) -Wall -o $@ $^

wait: wait.c
	$(CC) -Wall -o $@ $^

execl: execl.c
	$(CC) -Wall -o $@ $^

execv: execv.c
	$(CC) -Wall -o $@ $^

execve: execve.c
	$(CC) -Wall -o $@ $^

newpgm: newpgm.c
	$(CC) -Wall -o $@ $^

exe_ls: exe_ls.c
	$(CC) -Wall -o $@ $^

exe_test: exe_test.c
	$(CC) -Wall -o $@ $^

exe_test_02: exe_test_02.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
