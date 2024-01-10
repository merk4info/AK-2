ifneq ($(KERNELRELEASE),)

ccflags-y := -std=gnu11
ccflags-y += -I$(src)/inc
ccflags-y += -g -DDYNAMIC_DEBUG_MODULE

obj-m := test2/worm.o test1/hello.o

else

KDIR ?= /root/lab1/linux-stable

default:
	$(MAKE) -C $(KDIR) M=$$PWD
install:
	$(MAKE) -C $(KDIR) M=$$PWD modules_install
clean:
	$(MAKE) -C $(KDIR) M=$$PWD clean

endif
