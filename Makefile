all:
	mkdir -p ./bin/
	i686-elf-as boot.s -o ./bin/boot.o
	i686-elf-gcc -c kernel.c -o ./bin/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c ./drv/video.c -o ./bin/video.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o vtos.bin -ffreestanding -O2 -nostdlib ./bin/boot.o ./bin/video.o ./bin/kernel.o  -lgcc
test: all
	qemu-system-x86_64 -kernel vtos.bin 
clear:
	rm -rf ./bin/
clean:
	rm -rf ./bin/