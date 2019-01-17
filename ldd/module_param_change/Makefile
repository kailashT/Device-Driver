obj-m +=paramchange.o 
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
insert:
	insmod paramchange.ko param1=55 param2=45,88,44,66 paramstr="WorldTradeCenter"
remove:
	rmmod paramchange.ko
show:
	dmesg | tail -20
isload:
	lsmod | grep "paramchange"
