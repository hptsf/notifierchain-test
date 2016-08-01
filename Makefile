# Comment/uncomment the following line to disable/enable debugging
# DEBUG = y

# Add your debugging flag (or not) to CFLAGS
ifeq ($(DEBUG),y)
	DEBFLAGS = -O -g -DSCULL_DEBUG	 # "-O" is needed to expand inlines
else
	DEBFLAGS = -O2
endif
	
ifneq ($(KERNELRELEASE),)
# call from kernel build system
obj-m   := chain_0.o chain_1.o chain_2.o
else
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD       := $(shell pwd)

modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.markers *.order *.symvers

depend .depend dep:
	$(CC) $(CFLAGS) -M *.c > .depend


ifeq (.depend,$(wildcard .depend))
include .depend
endif
