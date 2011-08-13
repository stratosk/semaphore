obj-m += freq_table_sem.o

all:
	make -C /GT-I9000_Kernel/Kernel M=/GT-I9000_Kernel/Kernel/mymod modules
