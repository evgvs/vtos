#include "tvsh.h"

void tvsh_shell ()
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
			tty_printf("Available commands:\n", 0x0F);

			tty_printf("help ", 0x0E);
			tty_printf("- show this list\n", 0x0F);

			tty_printf("reboot ", 0x0E);
			tty_printf("- reboot system\n", 0x0F);

			tty_printf("info ", 0x0E);
			tty_printf("- show release info\n", 0x0F);

			tty_printf("clear ", 0x0E);
			tty_printf("- clear screen\n", 0x0F);

			tty_printf("vtfetch ", 0x0E);
			tty_printf("- show logo and release info\n", 0x0F);

			tty_printf("changelog ", 0x0E);
			tty_printf("- see what's new in this vtOS release\n", 0x0F);
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

			tty_printf("changelog ", 0x0E);
			tty_printf("- see what's new in this vtOS release\n", 0x0F);

			tty_printf("----------------------------------\n", 0x0f);

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
		else if ( strcmp ( cmd , "r test" ) == 0 )
		{
			tty_printf("press any key...", 0x0f);
			keyboard_getchar();
			tty_printf("\rRewrite test!!!!\n", 0x0A);
		}
		else if ( strcmp ( cmd , "panic-test" ) == 0 )
		{
			panic("test panic");
		}
		else if ( strcmp ( cmd , "changelog" ) == 0 )
		{
			tty_printf("New in vtOS 5:\nMemory paging and kernel heap\nBugfixes\nThis info\nInit and shell are now separated\nMultiple /n in string support\nRewrite line support (/r)\n", 0x0f);
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
