#ifndef _KERNEL_IDT_H_
#define _KERNEL_IDT_H_
#include <stdint.h>
#define IDT_NUM_ENTRIES 256
void idt_install();
void interrupt_enable_all();
void interrupt_disable_all();
#endif 
