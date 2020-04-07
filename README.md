# vtOS - open source operating system 

## Build & run
```
$ ./build.sh --test --iso # build and test in a qemu vm
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
*  Semi-working memory manager

## Booting vtOS on real hardware

#### Modern PCs
Make sure that legacy boot support (There is no UEFI video driver in vtOS), legacy usb support and something like "Port 60/64 Emulation" are enabled.

### Make an ISO file
```
$ ./build.sh --iso
```
### Write ISO file on disk
```
$ sudo dd if=vtos.iso of=/dev/sdX
```
