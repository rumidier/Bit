CC     := /usr/local/CodeSourcery/Sourcery_G++_Lite/bin/arm-none-eabi-gcc
obj-m  := ieb_dot.o
KDIR   := /Smart4412Linux/Development/Source/kernel/kernel_4412

all:
	make -C $(KDIR) SUBDIRS=$(PWD)

clean:	
	rm -rf *.o *.ko
	rm -rf *.mod.*
