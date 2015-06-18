
#obj-m := nosymbol.o symbol1.o symbol2.o
obj-m := macro_test.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.ko
	rm -rf *.mod.*
	rm -rf *.cmd
	rm -rf *.o
