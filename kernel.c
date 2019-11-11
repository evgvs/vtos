#include "./drv/video.h"
#include "./idt.h"
#include "./drv/keyboard.h"
#include "./lib/string.h"
#include "./panic.h"
#include "./io/ports.h"
#include "./gdt.h"
#include "./memory.h"
#include "power.h"

void tty_printfl ( int, char* );
void print_logo ( int );
void shell ();

void kernel_init () {
	display_clear(0x00);

    gdt_install();

    idt_install();

	interrupt_disable_all();

	keyboard_install();

	interrupt_enable_all();

	tty_printchar('\n', 0x0f);

	tty_printf(vtinfo_string(), 0x0f);

	tty_printchar('\n', 0x0f);

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

void shell ()
{
	char* PS1 = "[vtos | tvsh]$";
	while ( 1 )
	{
		//tty_printf("\n",0x0F);
		tty_printf(PS1, 0x07);
		tty_printf(" ", 0x0F);
		char* kgs = keyboard_getstring();
		// tty_printf(kgs, 0x0f);
		//TODO: arguments
		char* cmd = kgs ;

		//tty_printf("\n",0x0f);

		if ( strcmp ( cmd , "help" ) == 0 )
		{
			tty_printf("Available commands:\n ", 0x0F);

			tty_printf("help ", 0x0E);
			tty_printf("- show this list\n ", 0x0F);

			tty_printf("reboot ", 0x0E);
			tty_printf("- reboot system\n ", 0x0F);

			tty_printf("info ", 0x0E);
			tty_printf("- show release info\n ", 0x0F);

			tty_printf("clear ", 0x0E);
			tty_printf("- clear screen\n", 0x0F);

			tty_printf("vtfetch ", 0x0E);
			tty_printf("- show logo and release info\n", 0x0F);
		}
		else if ( strcmp ( cmd , "help --dev" ) == 0 )
		{
			tty_printf("Available commands:\n ", 0x0F);
			tty_printf("help ", 0x0E);
			tty_printf("- show this list\n ", 0x0F);

			tty_printf("info ", 0x0E);
			tty_printf("- show release info\n ", 0x0F);

			tty_printf("clear ", 0x0E);
			tty_printf("- clear screen\n", 0x0F);

			tty_printf("reboot ", 0x0E);
			tty_printf("- reboot system\n ", 0x0F);

			tty_printf("vtfetch ", 0x0E);
			tty_printf("- show logo and release info\n", 0x0F);

			tty_printf("----------------------------------", 0x0f);

			tty_printf("panic-test ", 0x0E);
			tty_printf("- call kernel panic\n", 0x0F);
		}
		else if ( strcmp ( cmd , "info" ) == 0 )
		{
			tty_printf(vtinfo_string(), 0x0f);
			tty_printchar('\n', 0x0f);
		}
		else if ( strcmp ( cmd , "logo" ) == 0 )
		{
			print_logo(0);
		}
		else if ( ( strcmp ( cmd , "vtfetch" ) == 0 ) | ( strcmp ( cmd , "logoi" ) == 0 ) )
		{
			print_logo(1);
		}
		else if ( strcmp ( cmd , "clear" ) == 0 )
		{
			display_clear(0x00);
		}
		else if ( strcmp ( cmd , "reboot" ) == 0 )
		{
			reboot();
		}
		else if ( strcmp ( cmd , "panic-test" ) == 0 )
		{
			panic("test panic");
		}
		else if ( strcmp( cmd , "" ) == 0 )
		{
			memset(cmd, 0, sizeof(cmd));
			memset(kgs, 0, sizeof(kgs));
			continue;
		}
		else
		{
			tty_printf("error", 0x04);
			tty_printf(": command '", 0x0F); 
			tty_printf( cmd , 0x0F); 
			tty_printf("' not found.\n", 0x0F);
		}
		memset(cmd, 0, sizeof(cmd));
		memset(kgs, 0, sizeof(kgs));
	}
}
