#include <interrupts.h>
#include <pit.h>

void pit_install() {
	timer_ticks = 0;
	register_interrupt_handler(TIMER_IDT_INDEX, pit_handler);
}

void pit_handler()
{
	++timer_ticks;
}
