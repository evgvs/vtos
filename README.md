# vtOS - open source operating system 

## Build & run
```
$ ISO=1 ./build.sh 
$ qemu-system-i386 -cdrom bootable.iso
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

## Booting vtOS on real hardware

#### Modern PCs
Make sure that legacy boot support (There is no UEFI video driver in vtOS), legacy usb support and something like "Port 60/64 Emulation" are enabled.

### Make an ISO file
```
$ ISO=1./build.sh
```
### Write ISO file on disk
```
# dd if=vtos.iso of=/dev/sdX
```
