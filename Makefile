AS = i686-elf-as
CC = i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O0  -c
all:
	mkdir 					-p isofiles/boot/grub/
	mkdir 					-p ./bin/
	$(AS) boot.s 				-o ./bin/boot.o
	$(AS) gdt_asm.s 			-o ./bin/gdt_asm.o
	$(AS) idt_asm.s 			-o ./bin/idt_asm.o
	$(AS) interrupts_asm.s 			-o ./bin/interrupts_asm.o
	$(CC) $(CFLAGS) info.c 			-o ./bin/info.o 
	$(CC) $(CFLAGS) gdt.c 			-o ./bin/gdt.o 
	$(CC) $(CFLAGS) kernel.c 		-o ./bin/kernel.o 
	$(CC) $(CFLAGS) idt.c 			-o ./bin/idt.o  
	$(CC) $(CFLAGS) panic.c 			-o ./bin/panic.o  
	$(CC) $(CFLAGS) interrupts.c 		-o ./bin/interrupts.o 
	$(CC) $(CFLAGS) ./lib/string.c 		-o ./bin/string.o 
	$(CC) $(CFLAGS) ./io/ports.c 		-o ./bin/ports.o 
	$(CC) $(CFLAGS) ./drv/keyboard.c 	-o ./bin/keyboard.o 
	$(CC) $(CFLAGS) ./drv/video.c 		-o ./bin/video.o 
	$(CC) $(CFLAGS) ./memory.c 			-o ./bin/memory.o 
	$(CC) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc 	
qemu: iso
	qemu-system-i386 -cdrom vtos.iso
iso: all
	cp vtos.bin isofiles
	grub-mkrescue -o vtos.iso isofiles
iso-qemu: iso
	qemu-system-i386 -cdrom vtos.iso
clean:
	rm -rf ./bin/
clear:
	rm -rf ./bin/
