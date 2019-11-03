all:
	mkdir -p ./bin/
	i686-elf-as boot.s -o ./bin/boot.o
	i686-elf-as idt_asm.s -o ./bin/idt_asm.o
	i686-elf-as interrupts_asm.s -o ./bin/interrupts_asm.o
	i686-elf-gcc -c kernel.c -o ./bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c idt.c -o ./bin/idt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c interrupts.c -o ./bin/interrupts.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c ./io/ports.c -o ./bin/ports.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c ./drv/keyboard.c -o ./bin/keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c ./drv/video.c -o ./bin/video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o vtos.bin -ffreestanding -O2 -nostdlib ./bin/*.o  -lgcc
test: all
	qemu-system-x86_64 -kernel vtos.bin 
clear:
	rm -rf ./bin/
clean:
	rm -rf ./bin/
