# vtOS - open source operating system 

## Build & run

### Enter build environment

```
$ ./env.sh
(vtos_env) $ make qemu # build and test in a qemu vm
```

### Make an ISO file

#### Create dirs and copy kernel inside isofiles/boot

```
$ mkdir -p isofiles/boot/grub
$ cp vtos.bin isofiles/boot/vtos.bin
```

#### Create grub.cfg inside isofiles/boot/grub directory and fill it with:

```
set timeout=0
set default=0

menuentry "vtOS" {
    multiboot2 /boot/vtos.bin
    boot
}
```

Final layout:

```
isofiles/
└── boot
    ├── grub
    │   └── grub.cfg
    └── vtos.bin
```

#### Make an entire ISO file with `grub-mkrescue`

```
$ grub-mkrescue -o vtOS.iso isofiles
```

## Features
*  Kernel
*  Print color text on screen
*  Keyboard 
*  Ports IO
*  Panic
*  Shell
