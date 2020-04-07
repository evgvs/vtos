#include <panic.h>
#include <string.h>
void panicrun(char * text, char * file, int line)
{
	display_clear(0x4f);
	tty_printf("\n", 0x4f);
	tty_printf("BRUH MOMENT\n", 0x4f);
	tty_printf("Panic at ", 0x4f);
	tty_printf(file, 0x4f);
	tty_printf(", line ", 0x4f);
	tty_printf(itoa(line), 0x4f);
	tty_printf(" !\n", 0x4f);
	tty_printf("System says: '", 0x4f);
	tty_printf(text, 0x4f);
	tty_printf("' \n", 0x4f);
	tty_printf("Before reporting a bug make sure you are using the latest version\n", 0x4f);
	tty_printf("from our git repository: gitlab.com/vt_/vtos \n \n", 0x4f);
	tty_printf("Press any key to reboot. \n", 0x4f);
	keyboard_getchar();
	reboot();
}
