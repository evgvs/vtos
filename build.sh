#!/bin/bash
CC="i686-elf-gcc"
AS="i686-elf-as"
CFLAGSO="-std=gnu99 -ffreestanding -O0  -c "
ASFLAGSO=" "

CFLAGS="$CFLAGSO -w"
ASFLAGS="$ASFLAGSO -W"
nshf=1

while [[ "$1" ]]; do
	case $1 in
		'--iso' | '-t')
			iso=1
		;;
		'--test')
			qemu=1
		;;
	        '--test2')
			qemu=2
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
		'-w' | '--show-warnings')
			CFLAGS="$CFLAGSO"
			ASFLAGS="$ASFLAGSO"
		;;
		'-h' | '--help') 
			shhelp=1
		;;
		'-f')
			unset nshf
		;;

	esac
	shift
done

shhelp(){
echo -e "
vtos/build.sh by tvsclass.

Keys:
\e[33m--iso  \e[0m      - Make vtos.iso file.

\e[33m--test \e[0m      - Run qemu after building.

\e[33m-k     \e[0m      - Compile only kernel.c.
\e[33m--only-kernel \e[0m

\e[33m-n\e[32m <file> \e[0m   - Compile only \e[32m<file>\e[0m
\e[33m--only \e[32m<file>\e[0m

\e[33m-w     \e[0m      - Don't show warnings.
\e[33m--ignore-warnings\e[0m

\e[33m-h      \e[0m     - Show this help.

"
}

shf(){
	! [[ $nshf ]] && echo $CFLAGS
}

shfa() {
	! [[ $nshf ]] && echo $ASFLAGS
}

unpack(){
	echo Unpacking i686-elf.tar.gz, please wait...
	tar -xf i686-elf.tar.gz
	echo -e "\e[32mDone.\e[0m"
}

make(){
	mkdir                                   -p isofiles/boot/grub/
	mkdir                                   -p ./bin/
	mkdir                                   -p isofiles/boot/grub/
        rm -rf ./bin/*.o
        $(AS) boot.s                        -o ./bin/boot.o
        $(AS) gdt_asm.s                     -o ./bin/gdt_asm.o
        $(AS) idt_asm.s                     -o ./bin/idt_asm.o
        $(AS) interrupts_asm.s              -o ./bin/interrupts_asm.o
        $(CC) info.c                  		-o ./bin/info.o
        $(CC) gdt.c                   		-o ./bin/gdt.o
        $(CC) init.c                		-o ./bin/init.o
        $(CC) idt.c                   		-o ./bin/idt.o
        $(CC) panic.c                       -o ./bin/panic.o
        $(CC) power.c                       -o ./bin/power.o
        $(CC) interrupts.c            		-o ./bin/interrupts.o
        $(CC) tvsh.c            			-o ./bin/tvsh.o
	$(CC) ./lib/split.c                     -o ./bin/split.o
        $(CC) ./lib/string.c          		-o ./bin/string.o
        $(CC) ./io/ports.c            		-o ./bin/ports.o
        $(CC) ./drv/keyboard.c        		-o ./bin/keyboard.o
        $(CC) ./drv/video.c           		-o ./bin/video.o
        $(CC) ./memory/kheap.c            	-o ./bin/kheap.o
        $(CC) ./memory/ordered_array.c      -o ./bin/ordered_array.o
        $(CC) ./memory/paging.c		        -o ./bin/paging.o -masm=intel
        $(CCNA) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc 
}

len(){
	expr length  "$1"
}
CCG(){
	export PATH="$(pwd)/i686-elf/bin:$PATH"
	! [[ $nshf ]] && echo -e "Executing: " "\e[32m$CC $(shf) $*\e[0m"
	if [[ $hide1 ]]; then
		! $CC $CFLAGS $* 1>/dev/null && exit 2;
	elif ! [[ $nshf ]]; then
		! $CC $CFLAGS $* && exit 2;
	else

                size=$(stty size | awk '{print $2}')

		let size=$size-$(len "Executing: ")
		printf "Executing: "

                size14=" "

                let size=$size-$(len $CC)
                printf "\e[32m$CC\e[0m"

		let size=$size-$(len " $*")
                while [[ ${size} > 0 ]]; do
                        printf " " 
                        let size=$size-1;
                done

                echo -ne "\e[33m $*\e[0m";
		echo
                ! $CC $CFLAGS $* && exit 2;
	fi
}

ASM(){
	export PATH="$(pwd)/i686-elf/bin:$PATH"
	! [[ $nshf ]] && echo -e "Executing: " "\e[32m$AS $(shfa) $*\e[0m"
	if [[ $hide1 ]]; then
		! $AS $ASFLAGS $* 1> /dev/null && exit 2;
	elif ! [[ $nshf ]]; then
		! $AS $ASFLAGS $* && exit 2;
	else
		size=$(stty size | awk '{print $2}')                  
                let size=$size-$(len "Executing: ")
                printf "Executing: "
                                                                                      size14=" "                                            
                let size=$size-$(len $AS)
                printf "\e[32m$AS\e[0m"

                let size=$size-$(len "$*")
                while [[ ${size} > 0 ]]; do                                                   printf " "
                        let size=$size-1;                                             done

                echo -ne "\e[33m$*\e[0m";
                echo
                ! $AS $ASFLAGS $* && exit 2;

	fi
}

CCANAG(){
	size=$(stty size | awk '{print $2}')
	while [[ $size > 0 ]]; do echo -ne "\e[33m=\e[0m" && let size=$size-1; done
	echo -e "Executing: \e[32m $CC $* -w \e[0m"
	! $CC $* && exit 2
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

CCNA(){
	echo CCANAG
}

OPT(){
	[[ $iso ]] && cp vtos.bin isofiles && grub-mkrescue -o vtos.iso isofiles
	[[ $qemu == 1 ]] && qemu-system-x86_64 -cdrom vtos.iso -m 64 
	[[ $qemu == 2 ]] && qemu-system-x86_64 -kernel vtos.iso -m 64
}


if [[ $onlykernel ]]; then
$(CC)  kernel.c                -o ./bin/kernel.o
$(CCNA) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc
exit 0;
fi

if [[ $only ]]; then
wo0=$(echo $whatonly | tr "/" " ")
abc=-1
for w in $wo0; do
let abc+=1;
done
a=( $wo0 )
wo=${a[$abc]}
wo1=${wo::-2}
$(CC) ${whatonly}               -o ./bin/$wo1.o
$(CCNA) -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc
exit 0;
fi

[[ $shhelp ]] && shhelp && exit 0

################

[[ -f ./bin/tv-shell.o ]] && rm ./bin/tv-shell.o 
! [[ -d $(pwd)/i686-elf/ ]] && unpack
make
OPT

################
