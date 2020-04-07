#include <interrupts.h>
#include <ports.h>
#include <idt.h>
#include <drv/video.h>
#include <panic.h>

static interrupt_handler_t interrupt_handlers[IDT_NUM_ENTRIES];

bool register_interrupt_handler(uint32_t idt_index, interrupt_handler_t handler)
{
    if (idt_index >= IDT_NUM_ENTRIES)
    {
        return false;
    }

    if (interrupt_handlers[idt_index] != NULL)
    {
        return false;
    }

    interrupt_handlers[idt_index] = handler;
    return true;
}

void fault_handler(struct regs *r)
{
    panic("interrupt error");
}

void irq_handler(struct regs *r)
{
    // Blank function pointer
    void (*handler)(struct regs * r);

    // If there's a custom handler to handle the IRQ, handle it
    handler = interrupt_handlers[r->idt_index];
    if (handler)
    {
        handler(r);
    }

    // If the IDT entry that was invoked was greater than 40, sends an EOI
    // to the slave controller
    if (r->idt_index >= 40)
    {
        outb(0xA0, 0x20);
    }

    // Sends an EOI to the master interrupt controller
    outb(0x20, 0x20);
}

void run_interrupt_handler(struct regs* r)
{
    size_t idt_index = r->idt_index;
    if (idt_index < 32)
    {
        fault_handler(r);
        return;
    }

    if (idt_index >= 32 && idt_index <= 47)
    {
        irq_handler(r);
        return;
    }

    if (interrupt_handlers[r->idt_index] != 0)
    {
        interrupt_handlers[r->idt_index](r);
    }
}
