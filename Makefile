obj-m += msi-laptop.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

test:
	sudo dmesg -C
	sudo insmod msi-laptop.ko
	sudo rmmod msi_laptop.ko
	dmesg
