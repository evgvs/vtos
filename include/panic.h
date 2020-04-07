#ifndef PANIC_H
#define PANIC_H

#include <drv/video.h>
#include <power.h>
#include <drv/keyboard.h>
#define panic(msg) panicrun(msg, __FILE__, __LINE__)
extern void panicrun(char * text, char * file, int line); 
#endif // PANIC_H
