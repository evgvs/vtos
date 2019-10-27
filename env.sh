#!/bin/sh

! [ -f "i686-elf-4.9.1-Linux-x86_64/" ] && tar xf 'i686-elf-4.9.1-Linux-x86_64.tar.xz'

PS1="(vtos_env) $PS1" PATH="$(pwd)/i686-elf-4.9.1-Linux-x86_64/bin:$PATH" $SHELL
