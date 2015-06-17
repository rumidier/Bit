CFLAGS=-g

minish : mini_sh.o fs.o diskemul.o
	gcc $(CFLAGS) -o minish mini_sh.o fs.o diskemul.o

mini_sh.o : mini_sh.c
	gcc $(CFLAGS) -c mini_sh.c

fs.o : fs.c fs.h disk_driver.h
	gcc $(CFLAGS) -c fs.c

diskemul.o : diskemul.c disk_driver.h
	gcc $(CFLAGS) -c diskemul.c

clean:
	rm *.o
	rm minish.exe
