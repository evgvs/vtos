# vtOS-OSS-2020
My cringe osdev project from the good old times (2019-2020), with contributions from `tvsclass`: build script, "shell", some string functions and other. There was a version with initrd support, but it was never pushed into git. Posted on github because vtOS brings me a lot of pleasant nostalgic memories. In fact, this is my first project in C language, I was young and naive, had stolen a little bit of code and made my own "operating system".

Build kernel and run vtOS (to create ISO file, run `ISO=1 ./build.sh`):
```
git clone https://github.com/evgvs/vtos
cd vtos
./build.sh 
qemu-system-i386 -kernel vtos.bin
```

## Features
*  Kernel
*  Print color text on screen
*  Keyboard 
*  Ports IO
*  Panic
*  Shell
*  GRUB boot support
*  Higer Half kernel
*  PIT
*  Semi-working memory manager
*  VFS

## Real hardware
Enable following in BIOS:
* Legacy boot
* Legacy USB
* Port 60/64 Emulation
