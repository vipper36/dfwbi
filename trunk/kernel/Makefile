obj-m += udpser.o
udpser-objs := udpserver.o
KERNELBUILD := /lib/modules/$(shell uname -r)/build

default:
	make -C $(KERNELBUILD) M=$(shell pwd) modules

install:
	insmod ./udpser.ko
clean:
	rm -f *.o *.cmd *.ko *.mod.c
