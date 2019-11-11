#!/bin/bash
CC="i686-elf-gcc"
AS="i686-elf-as"
CFLAGS="-std=gnu99 -ffreestanding -O0  -c "

while [[ $1 ]]; do
	case $1 in
		'--iso')
			iso=1
		;;
		'--test')
			qemu=1
		;;
		'--hide-1')
			hide1=1
		;;
		'-k' | '--only-kernel')
			onlykernel=1
		;;
		'-n' | '--only')
			shift 
			only=1
			whatonly=$1
		;;
	esac
	shift
done

unpack(){
	echo Unpacking i686-elf.tar.gz, please wait...
	tar -xf i686-elf.tar.gz
	echo -e "\e[32mDone.\e[0m"
}

make(){
	mkdir                               -p isofiles/boot/grub/
	mkdir                               -p ./bin/
	mkdir                                   -p isofiles/boot/grub/
        mkdir                                   -p ./bin/
        $(AS) boot.s                            -o ./bin/boot.o
        $(AS) gdt_asm.s                         -o ./bin/gdt_asm.o
        $(AS) idt_asm.s                         -o ./bin/idt_asm.o
        $(AS) interrupts_asm.s                  -o ./bin/interrupts_asm.o
        $(CC) $(CFLAGS) info.c                  -o ./bin/info.o
        $(CC) $(CFLAGS) gdt.c                   -o ./bin/gdt.o
        $(CC) $(CFLAGS) kernel.c                -o ./bin/kernel.o
        $(CC) $(CFLAGS) idt.c                   -o ./bin/idt.o
        $(CC) $(CFLAGS) panic.c                         -o ./bin/panic.o
        $(CC) $(CFLAGS) interrupts.c            -o ./bin/interrupts.o
        $(CC) $(CFLAGS) ./lib/string.c          -o ./bin/string.o
        $(CC) $(CFLAGS) ./io/ports.c            -o ./bin/ports.o
        $(CC) $(CFLAGS) ./drv/keyboard.c        -o ./bin/keyboard.o
        $(CC) $(CFLAGS) ./drv/video.c           -o ./bin/video.o
        $(CC) $(CFLAGS) ./memory.c                      -o ./bin/memory.o
        $(CC) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc
}


CCG(){
	export PATH="$(pwd)/i686-elf/bin:$PATH"
	echo -e "Executing: " "\e[32m$CC $*\e[0m"
	if [[ $hide1 ]]; then
		! $CC $* 1>/dev/null && exit 2;
	else
		! $CC $* && exit 2;
	fi
}

ASM(){
	export PATH="$(pwd)/i686-elf/bin:$PATH"
	echo -e "Executing: " "\e[32m$AS $*\e[0m"
	if [[ $hide1 ]]; then
		! $AS $* 1> /dev/null && exit 2;
	else
		! $AS $* && exit 2;
	fi
}

CFLAGS(){
	echo $CFLAGS
}

CC(){
	echo CCG
}

AS(){
	echo ASM
}

OPT(){
	[[ $iso ]] && cp vtos.bin isofiles && grub-mkrescue -o vtos.iso isofiles
	[[ $qemu ]] && qemu-system-x86_64 -kernel vtos.bin 
}


if [[ $onlykernel ]]; then
$(CC) $(CFLAGS) kernel.c                -o ./bin/kernel.o
$(CC) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc
exit 0;
fi

if [[ $only ]]; then
wo=$(ls $whatonly)
wo1=${wo::-2}
$(CC) $(CFLAGS) ${whatonly}               -o ./bin/$wo1.o
$(CC) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc
exit 0;
fi

################

! [[ -d $(pwd)/i686-elf/ ]] && unpack
make
OPT

################
