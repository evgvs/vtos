# vtOS - open source operating system 

## Build & run

### Enter build environment

```
$ ./env.sh
(vtos_env) $ make qemu # build and test in a qemu vm
```
## Features
*  Kernel
*  Print color text on screen
*  Keyboard 
*  Ports IO
*  Panic
*  Shell
*  GRUB boot support 

## Booting vtOS on real hardware

#### Modern PCs
Make sure that legacy boot support (There is no UEFI video driver in vtOS), legacy usb support and something like "Port 60/64 Emulation" are enabled.

### Make an ISO file
```
$ make iso
```
### Write ISO file on disk
```
$ sudo dd if=vtos.iso of=/dev/sdX
```
