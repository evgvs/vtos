#include <power.h>
#include <ports.h>
void reboot()
{
	asm("cli");
    int good = 0x02;
    while (good & 0x02)
        good = inb(0x64);
    outb(0x64, 0xFE);
    for(;;);
}
