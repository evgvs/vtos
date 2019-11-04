#include "./drv/video.h"
#include "./idt.h"
#include "./drv/keyboard.h"
#include "./lib/string.h"
#include "./lib/string.c"

void tty_printfl ( int, char* );
void print_logo ( int );
void shell ();

void kernel_init (void) {
	display_clear(0x00);
	tty_printf("     STARTING UP VTOS\n", 0x0e);
	// print_logo();


	tty_printf("starting IDT...\n", 0x0f);
	idt_install();
	tty_printf("IDT started\n", 0x02);

	interrupt_disable_all();
	tty_printf("interrupts disabled\n", 0x02);

	tty_printf("initializing keyboard...\n", 0x0f);
	keyboard_install();
	tty_printf("keyboard initialized\n", 0x02);

	interrupt_enable_all();
	tty_printf("interrupts enabled\n", 0x02);

	tty_printf(vtinfo_string(), 0x0f);
	tty_printf('\n', 0x0f);
	shell();
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
		tty_printfl(0x0F, "M");
		xxx++;
	}
	tty_printfl(0x0F, "\n");
	xxx=0;
	while (xxx < 6) {
		tty_printfl(0x0F, "M");
		xxx++;
	}
	tty_printfl(0x0F, "E");
	xxx=0;
	while (xxx < 5) {
		tty_printfl(0x02, "0");
		xxx++;
	}
	tty_printfl(0x0F, "XWMMMMMMMMMMMMMMMMMMMMMMMM  ");
	if ( with_info == 1 ) { tty_printf(vtinfo_string(), 0x0f); }
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMN");
	tty_printfl(0x02, "kkkkkkk");
	tty_printfl(0x0F, "KMMMMMMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMX");
	tty_printfl(0x02, "kkkxkkk");
	tty_printfl(0x0F, "XMMMMMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMXK");
	tty_printfl(0x02, "KKK");
	tty_printfl(0x0F, "XK0NMMMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMMMMMMN");
	tty_printfl(0x06, "OO");
	tty_printfl(0x0F, "MMMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMMMMMX");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "MX");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "MMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMMMW");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "XMMM");
	tty_printfl(0x06, "R");
	tty_printfl(0x0F, "XMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMMM");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "NMMMMW");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "NMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMMX");
	tty_printfl(0x06, "K");
	tty_printfl(0x0F, "MMMMMMW");
	tty_printfl(0x06, "OX");
	tty_printfl(0x0F, "MMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMW");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "WMMMMMMMM");
	tty_printfl(0x06, "KO");
	tty_printfl(0x0F, "WMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMN");
	tty_printfl(0x06, "O");
	tty_printfl(0x0F, "MMMMMMMMMMX");
	tty_printfl(0x04, "X0KWX0OO0X");
	tty_printfl(0x0F, "WMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMW");
	tty_printfl(0x04, "NXXKOK00KX");
	tty_printfl(0x0F, "WMMM");
	tty_printfl(0x04, "WX0OOOOOOOOOW");
	tty_printfl(0x0F, "MMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMM");
	tty_printfl(0x04, "NOOOOOOOOOOO0");
	tty_printfl(0x0F, "WM");
	tty_printfl(0x04, "XOOOOOOOOOOOOX");
	tty_printfl(0x0F, "MMMM");
	tty_printfl(0x0F, "\n"); 
	tty_printfl(0x0F, "MMMMM");
	tty_printfl(0x04, "NOOOOOOOOOOO0N");
	tty_printfl(0x0F, "M");
	tty_printfl(0x04, "XOOOOOOOOOOOOX");
	tty_printfl(0x0F, "MMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMM");
	tty_printfl(0x04, "NOOOOOOOOOOO0");
	tty_printfl(0x0F, "WM");
	tty_printfl(0x04, "XOOOOOOOOOOOOX");
	tty_printfl(0x0F, "MMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMM");
	tty_printfl(0x04, "W0OOOOOOOOOOX");
	tty_printfl(0x0F, "MMM");
	tty_printfl(0x04, "WKOOOOOOOOK");
	tty_printfl(0x0F, "WMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMW");
	tty_printfl(0x04, "XK0OOO00KN");
	tty_printfl(0x0F, "MMMMMM");
	tty_printfl(0x04, "WXXKXXN");
	tty_printfl(0x0F, "WMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
	tty_printfl(0x0F, "\n");
	tty_printfl(0x0F, "\n");
	tty_printfl(0xE2, "     vtOS");
}

void shell ()
{
	// /todo
	tty_printf("\n==VTOS KERNEL SHELL==\n",0x0e);
	char* PS1 = "vtos | tvsh >>>";
	while ( 1 )
	{
		tty_printf("\n",0x0F);
		tty_printf(PS1, 0x0F);
		tty_printf(" ", 0x0F);
		char* kgs=keyboard_getstring();
		// tty_printf(kgs, 0x0f);
		char* cmd = strtok ( strtok (kgs, " "),  "S") ;
		tty_printf("\n", 0x0F);
		//if
		//
		if ( strcmp ( cmd , "help" ) == 0 )
		{
			tty_printf("This is help. \n", 0x0F);
		}
		else if ( strcmp ( cmd , "info" ) == 0 )
		{
			tty_printf(vtinfo_string(), 0x0f);
		}
		else if ( strcmp ( cmd , "logo" ) == 0 )
		{
			print_logo(0);
		}
		else if ( ( strcmp ( cmd , "neofetch" ) == 0 ) | ( strcmp ( cmd , "logoi" ) == 0 ) )
		{
			print_logo(1);
		}
		else if ( strcmp ( cmd , "clear" ) == 0 )
		{
			display_clear(0x00);
		}
		else
		{
			tty_printf("error", 0x04);
			tty_printf(": command '", 0x0F); 
			tty_printf( cmd , 0x0F); 
			tty_printf("' not found.\n", 0x0F);
		}
		cmd="";
		kgs="";
		//
		//fi
	}
}
