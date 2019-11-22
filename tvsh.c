#include "tvsh.h"
#include "./memory/kheap.h"
#include "./lib/string.h"
#include "./power.h"
#include "./lib/split.c"

void tvsh_shell ()
{
	char* PS1 = "[vtos | tvsh]$";
	while ( 1 )
	{
		//tty_printf("\n",0x0F);
		tty_printf(PS1, 0x07);
		tty_printf(" ", 0x0F);

		char kgs[200];
		char* kgo = keyboard_getstring();
		// tty_printf(kgo , 0x0f );

	       	strcpy ( kgs , kgo  );
		
		// tty_printf(kgs, 0x0f);
		//TODO: arguments
		

		char* cmd = strtok ( kgs  , " " );
		char* arg1= strtok ( NULL , " " );
		char* arg2= strtok ( NULL , " " );
		char* arg3= strtok ( NULL , " " );
		char* arg4= strtok ( NULL , " " );
		char* arg5= strtok ( NULL , " " );
		char* arg6= strtok ( NULL , " " );
		char* arg7= strtok ( NULL , " " );
		char* arg8= strtok ( NULL , " " );
		char* arg9= strtok ( NULL , " " );



		//tty_printf( str_split ( kgs , " " , 1) , 0x0f );

		//tty_printf("\n",0x0f);

		if ( strcmp ( cmd , "help" ) == 0 )
		{
			tty_printf("Available commands:\n", 0x0F);

			tty_printf("help ", 0x0E);
			tty_printf("- show this list\n", 0x0F);

			tty_printf("echo ", 0x0E);
			tty_printf("- print text\n", 0x0F);

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
			if ( strcmp ( arg1 , "--dev" ) == 0 )
			{
			tty_printf("----------------------------------\n", 0x0f);

			tty_printf("args ", 0x0E);
			tty_printf("- test shell arguments\n", 0x0F);

			tty_printf("panic-test ", 0x0E);
			tty_printf("- call kernel panic\n", 0x0F);

			tty_printf("malloc-test ", 0x0E);
			tty_printf("- test vtOS kernel memory allocation\n", 0x0F);
			}
		}
		else if ( strcmp ( cmd , "info" ) == 0 )
		{
			tty_printf(vtinfo_string(), 0x0f);
			tty_printchar('\n', 0x0f);
		}
		else if ( strcmp ( cmd , "echo" ) == 0 )
		{
                        tty_printf(arg1, 0x0f);                                               tty_printf(" ", 0x0f);
			tty_printf(arg2, 0x0f);
                        tty_printf(" ", 0x0f);
                        tty_printf(arg3, 0x0f);                                               tty_printf(" ", 0x0f);
                        tty_printf(arg4, 0x0f);                                               tty_printf(" ", 0x0f);                      
                        tty_printf(arg5, 0x0f);                                               tty_printf(" ", 0x0f);                                                tty_printf(arg6, 0x0f);                                               tty_printf(" ", 0x0f);                       
                        tty_printf(arg7, 0x0f);
                        tty_printf(" ", 0x0f);
                        tty_printf(arg8, 0x0f);
                        tty_printf(" ", 0x0f);                                                tty_printf(arg9, 0x0f);                                               tty_printf(" ", 0x0f);
			tty_printf("\n", 0x0f);

		}
		else if ( strcmp ( cmd , "args" ) == 0 )
		{
			tty_printf("arg1: ", 0x0f);
			tty_printf(arg1, 0x0f);
			tty_printf("\n", 0x0f);
			tty_printf("arg2: ", 0x0f);
			tty_printf(arg2, 0x0f);
			tty_printf("\n", 0x0f);
			tty_printf("arg3: ", 0x0f);
			tty_printf(arg3, 0x0f);                                               tty_printf("\n", 0x0f);
			tty_printf("arg4: ", 0x0f);
			tty_printf(arg4, 0x0f);                                               tty_printf("\n", 0x0f);
			tty_printf("arg5: ", 0x0f);
			tty_printf(arg5, 0x0f);                                               tty_printf("\n", 0x0f);
			tty_printf("arg6: ", 0x0f);
			tty_printf(arg6, 0x0f);                                               tty_printf("\n", 0x0f);
			tty_printf("arg7: ", 0x0f);
			tty_printf(arg7, 0x0f);                                               tty_printf("\n", 0x0f);
			tty_printf("arg8: ", 0x0f);
			tty_printf(arg8, 0x0f);                                               tty_printf("\n", 0x0f);
			tty_printf("arg9: ", 0x0f);
			tty_printf(arg9, 0x0f);                                               tty_printf("\n", 0x0f);

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
		else if ( strcmp ( cmd , "malloc-test" ) == 0 )
		{
			int *a;  
			int i, n;
			tty_printf("enter int array size: ",0x0f);
			n = atoi(keyboard_getstring());
			a = (int*)kmalloc(n * sizeof(int));
			for (i = 0; i<n; i++)
			{
				tty_printf("enter element of array: ", 0x0f);
				a[i] = atoi(keyboard_getstring());
			}
			tty_printf("your dynamic array: ");
			for (i = 0; i<n; i++) {
				tty_printf(itoa(a[i]), 0x0f);
				tty_printf(" ", 0x0f);
			}
			kfree(a);
			tty_printf("\nArray deleted. Memory cleaned.\n");
		}
		else if ( strcmp ( cmd , "panic-test" ) == 0 )
		{
			panic("test panic");
		}
		else if ( strcmp ( cmd , "reboot" ) == 0 )
		{
			reboot();
		}
		else if ( strcmp ( cmd , "changelog" ) == 0 )
		{
			tty_printf("New in vtos 5: \necho command\nhelp command update\n", 0x0f);
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
