AS = i686-elf-as
CC = i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O0 -Wall -Wextra -c
all:
	mkdir -p ./bin/
	$(AS) boot.s 				-o ./bin/boot.o
	$(AS) idt_asm.s 			-o ./bin/idt_asm.o
	$(AS) interrupts_asm.s 			-o ./bin/interrupts_asm.o
	$(CC) $(CFLAGS) info.c 			-o ./bin/info.o 
	$(CC) $(CFLAGS) kernel.c 		-o ./bin/kernel.o 
	$(CC) $(CFLAGS) idt.c 			-o ./bin/idt.o  
	$(CC) $(CFLAGS) panic.c 			-o ./bin/panic.o  
	$(CC) $(CFLAGS) interrupts.c 		-o ./bin/interrupts.o 
	$(CC) $(CFLAGS) ./io/ports.c 		-o ./bin/ports.o 
	$(CC) $(CFLAGS) ./drv/keyboard.c 	-o ./bin/keyboard.o 
	$(CC) $(CFLAGS) ./drv/video.c 		-o ./bin/video.o 
	$(CC) -T linker.ld -o vtos.bin -ffreestanding -O2 -nostdlib ./bin/*.o  -lgcc 	
qemu: all
	qemu-system-i386 -kernel vtos.bin 
clear:
	rm -rf ./bin/
clean:
	rm -rf ./bin/

