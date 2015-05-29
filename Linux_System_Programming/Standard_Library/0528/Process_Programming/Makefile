CC = gcc

PROGRAMS = argc environ putenv  fork

all: $(PROGRAMS)

argc: argc.c
	$(CC) -Wall -o $@ $^

environ: environ.c
	$(CC) -Wall -o $@ $^

putenv: putenv.c
	$(CC) -Wall -o $@ $^

fork: fork.c
	$(CC) -Wall -o $@ $^

clean:
	rm -rf $(PROGRAMS)
