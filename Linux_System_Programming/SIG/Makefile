CC = gcc

PROGRAMS= ignore alarm kill2 pipe pipe_02 pipe_03 raise sig_child signal_1 sigprocmask binpipen_01 kill popen sig_01 sig_parent signal_2 sigpending

all: $(PROGRAMS)

alarm: alarm.c 
	$(CC) -Wall -o $@ $^
ignore: ignore.c 
	$(CC) -Wall -o $@ $^
kill2: kill2.c 
	$(CC) -Wall -o $@ $^
pipe: pipe.c 
	$(CC) -Wall -o $@ $^
pipe_02: pipe_02.c 
	$(CC) -Wall -o $@ $^
pipe_03: pipe_03.c 
	$(CC) -Wall -o $@ $^
raise: raise.c 
	$(CC) -Wall -o $@ $^
sig_child: sig_child.c 
	$(CC) -Wall -o $@ $^
signal_1: signal_1.c 
	$(CC) -Wall -o $@ $^
sigprocmask: sigprocmask.c 
	$(CC) -Wall -o $@ $^
binpipen_01: binpipen_01.c 
	$(CC) -Wall -o $@ $^
kill: kill.c 
	$(CC) -Wall -o $@ $^
popen: popen.c 
	$(CC) -Wall -o $@ $^
sig_01: sig_01.c 
	$(CC) -Wall -o $@ $^
sig_parent: sig_parent.c 
	$(CC) -Wall -o $@ $^
signal_2: signal_2.c 
	$(CC) -Wall -o $@ $^
sigpending: sigpending.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
