#!/usr/bin/env bash

setupenv() {
	export PATH="$PATH:./gcc-8.1.0-nolibc/x86_64-linux/bin/"
	export CC="x86_64-linux-gcc"
	export AS="x86_64-linux-as"
    	export CFLAGS="-I include -I lib/include -std=gnu99 -ffreestanding -O0  -c -w"
	export ASFLAGS="-W"
}

gcccheck() {
	if ! [[ -d gcc-8.1.0-nolibc ]]
    	then
        	echo x86_64-cross not found.
        	echo Downloading x86_64-cross.tar.xz...
        	curl -LO https://files.vtsoft.dev/x86_64-cross.tar.xz
        	echo Unpacking i686-elf.tar.xz...
        	tar -xf x86_64-cross.tar.xz &> /dev/null
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
	$CC -T linker.ld -o vtos.bin -ffreestanding -O0 -nostdlib ./bin/*.o  -lgcc
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
