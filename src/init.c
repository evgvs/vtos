#include <drv/video.h>
#include <idt.h>
#include <drv/keyboard.h>
#include <string.h>
#include <panic.h>
#include <ports.h>
#include <gdt.h>
#include <power.h>
#include <tvsh.h>
#include <info.h>
#include <common.h>
#include <pit.h>
#include <multiboot.h>
#include <fs/fs.h>

void kernel_init (int magic, struct multiboot_info *mboot_info) {
	display_clear(0x00);
	tty_printchar('\n', 0x0f);
	tty_printf("Display initialized\n", 0x0B);

    	gdt_install();
    	idt_install();
    	tty_printf("GDT & IDT initialized\n", 0x0B);

	interrupt_disable_all();

	keyboard_install();
	pit_install();
	
	tty_printf("Keyboard initializedn\n", 0x0B);

	interrupt_enable_all();
	tty_printf("Interrupts enabled\n", 0x0B);
	
	fs_init();
	
	if (!mboot_info->mods_count)
		tty_printf("No modules found!\n", 0x04);
		
	tty_printf("Welcome to vtOS ", 0x0f);
	tty_printf(VTOS_VERSION, 0x0f);
	if (VTOS_TESTING)
		tty_printf(" (testing)", 0xE);
	tty_printf("!\n", 0x0f);
	
	tty_printf("Compiled at ", 0x0f);
	tty_printf(__DATE__, 0x0f);
	tty_printf(", ", 0x0f);
	tty_printf(__TIME__, 0x0f);
	tty_printf("\n", 0x0f);
	
	tty_printchar('\n', 0x0f);

	tvsh_shell();
	return;
}

