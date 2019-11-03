#!/bin/sh

tar -xf ./i686-elf.tar.gz

PROMPT="(vtos_env) $(echo $PROMPT)" 
PS1="(vtos_env) $(echo $PS1)" 
PATH="$(pwd)/i686-elf/bin:$PATH" $SHELL
