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

void kernel_init () {
	display_clear(0x00);
	tty_printchar('\n', 0x0f);
	tty_printf("Display initialized\n", 0x0B);

    	gdt_install();
    	idt_install();
    	tty_printf("GDT & IDT initialized\n", 0x0B);

	interrupt_disable_all();

	keyboard_install();
	tty_printf("Keyboard initializedn\n", 0x0B);

	interrupt_enable_all();
	tty_printf("Interrupts enabled\n", 0x0B);

	//initialise_paging(); //paging is already enabled in higer half

	tty_printf("Welcome to vtOS ", 0x0f);
	tty_printf(VTOS_VERSION, 0x0f);
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

void tty_printfl ( int color , char* str )
{
	tty_printf(str, color);
}

void print_logo ( int with_info )
{
	/// /done
	 int xxx = 0;
	while (xxx < 38) {
		tty_printfl(0x0F, " ");
		xxx++;
	}
	tty_printfl(0x0F, "\n");
	xxx=0;
	while (xxx < 6) {
		tty_printfl(0x0F, " ");
		xxx++;
	}
	tty_printfl(0x0F, "");
	xxx=0;
	while (xxx < 5) {
		tty_printfl(0x02, "0");
		xxx++;
	}
	tty_printfl(0x02, "XWX                          ");
	if ( with_info == 1 ) { tty_printf(vtinfo_string(), 0x0f); }
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "       ");
	tty_printfl(0x02, "kkkkkkk");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "        ");
	tty_printfl(0x02, "kkkxkkk");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "          ");
	tty_printfl(0x02, "KKKKKkk");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "                ");
	tty_printfl(0x06, "OO");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "               ");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "  ");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "             ");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "    ");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "            ");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "      ");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "            ");
	tty_printfl(0x06, "K");
	tty_printfl(0x0F, "       ");
	tty_printfl(0x06, "OX");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "           ");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "         ");
	tty_printfl(0x06, "KO");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "           ");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "           ");
	tty_printfl(0x04, "X0KWX0OO0X");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "       ");
	tty_printfl(0x04, "NXXKOK00KX");
	tty_printfl(0x0F, "    ");
	tty_printfl(0x04, "WX0OOOOOOOOOW");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "     ");
	tty_printfl(0x04, "NOOOOOOOOOOO0");
	tty_printfl(0x0F, "  ");
	tty_printfl(0x04, "XOOOOOOOOOOOOX");
	tty_printfl(0x0F, "\n"); 
	tty_printfl(0x0F, "     ");
	tty_printfl(0x04, "NOOOOOOOOOOO0N");
	tty_printfl(0x0F, " ");
	tty_printfl(0x04, "XOOOOOOOOOOOOX");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "     ");
	tty_printfl(0x04, "NOOOOOOOOOOO0");
	tty_printfl(0x0F, "  ");
	tty_printfl(0x04, "XOOOOOOOOOOOOX");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "     ");
	tty_printfl(0x04, "W0OOOOOOOOOOX");
	tty_printfl(0x0F, "   ");
	tty_printfl(0x04, "WKOOOOOOOOK");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "       ");
	tty_printfl(0x04, "XK0OOO00KN");
	tty_printfl(0x0F, "      ");
	tty_printfl(0x04, "WXXKXXN");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "                                      ");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x02, "                                       vtOS\n");
}

int  y_itoa(int value,char *ptr)
{
	int count=0,temp;
	if(ptr==NULL)
		return 0;
	if(value==0)
	{
		*ptr='0';
		return 1;
	}
	
	if(value<0)
	{
		value*=(-1);
		*ptr++='-';
		count++;
	}
	for(temp=value;temp>0;temp/=10,ptr++);
	*ptr='\0';
	for(temp=value;temp>0;temp/=10)
	{
		*--ptr=temp%10+'0';
		count++;
	}
	return count;
}

