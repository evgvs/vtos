#!/usr/bin/env bash

setupenv() {
	export PATH="$PATH:./i686-elf/bin/"
	export CC="i686-elf-gcc"
	export AS="i686-elf-as"
    export CFLAGS="-I include -I lib/include -std=gnu99 -ffreestanding -O1  -c 
    -w"
	export ASFLAGS="-W"
    export INCLUDE="-I include -I lib/include"
}

gcccheck() {
	if ! [[ -d i686-elf ]]
    then
        echo i686-elf-tools not found.
        echo Downloading i686-elf.tar.xz...
        curl -LO files.vtsoft.dev/i686-elf.tar.xz
        echo Unpacking i686-elf.tar.xz...
        tar -xf i686-elf.tar.xz &> /dev/null
	fi
}

run() {
	while [[ $1 ]]
	do
		case $1 in
			'-v')
				VERBOSE=1
				;;
		esac
		shift
	done

	gcccheck
	setupenv
	main
}

log() {
	if [[ $VERBOSE ]]
	then
		echo $*
	fi
}

cc() {
	for file in $*
	do

		wo0=$(echo $file | tr "/" " ")
		abc=-1
		for w in $wo0 
		do
			let abc+=1;
		done
		a=( $wo0 )
		wo=${a[$abc]}
		wo1=${wo::-2}
		
        echo -e "\e[2m[compiling]\e[22m \e[34m$file\e[39m => \e[36m$wo1.o\e[39m"

        $CC $CFLAGS $file -o ./bin/$wo1.o
	done
}

as() {
	for file in $*
	do

		wo0=$(echo $file | tr "/" " ")
		abc=-1
		for w in $wo0 
		do
			let abc+=1;
		done
		a=( $wo0 )
		wo=${a[$abc]}
		wo1=${wo::-2}
		
        echo -e "\e[2m[compiling]\e[22m \e[34m$file\e[39m => \e[36m$wo1.o\e[39m"

		$AS $ASFLAGS $file -o ./bin/$wo1.o
	done
}

lk() {
	i686-elf-gcc -T linker.ld -o vtos.bin -ffreestanding -O1 -nostdlib ./bin/*.o  -lgcc
}

main() {
	cfiles=$( find ./ -name '*.c' ) ; log cfiles $cfiles
	asfiles=$( find ./ -name '*.s') ; log asfiles $asfiles
    
    mkdir -p ./bin/
    mkdir -p ./isofiles/
	cc $cfiles
	as $asfiles
    lk  
    
    if [[ $ISO -eq 1 ]]
    then
        cp ./vtos.bin isofiles
        grub-mkrescue -o bootable.iso isofiles
    fi
}

run $*
