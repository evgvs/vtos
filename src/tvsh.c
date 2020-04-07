#include <tvsh.h>
#include <memory.h>
#include <string.h>
#include <power.h>
#include <split.h>
#include <panic.h>
#include <info.h>
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
		//    //   //TODO: arguments
		
		char** args = split ( kgs , " " );

		char* cmd = args[0];



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

			tty_printf("calc x [+,-,*,/] y ", 0x0E);
			tty_printf(" - calculator\n", 0x0F);

			tty_printf("clear ", 0x0E);
			tty_printf("- clear screen\n", 0x0F);

			tty_printf("vtfetch ", 0x0E);
			tty_printf("- show logo and release info\n", 0x0F);

			tty_printf("changelog ", 0x0E);
			tty_printf("- see what's new in this vtOS release\n", 0x0F);
			if ( strcmp ( args[1] , "--dev" ) == 0 )
			{
			tty_printf("----------------------------------\n", 0x0f);

			tty_printf("args ", 0x0E);
			tty_printf("- test shell arguments\n", 0x0F);

			tty_printf("panic-test ", 0x0E);
			tty_printf("- call kernel panic\n", 0x0F);

			tty_printf("malloc-test ", 0x0E);
			tty_printf("- vtOS malloc demo 1 - dynamic arrays\n", 0x0F);
			
			tty_printf("malloc [size] ", 0x0E);
			tty_printf("- vtOS malloc demo 2 - try to malloc [size] in bytes\n", 0x0F);
			}
		}
		else if ( strcmp ( cmd , "info" ) == 0 )
		{
			tty_printf("vtOS ", 0x0f);
			tty_printf(VTOS_VERSION, 0x0f);
			tty_printf(" Compiled at ", 0x0f);
			tty_printf(__DATE__, 0x0f);
			tty_printf(", ", 0x0f);
			tty_printf(__TIME__, 0x0f);
			tty_printf("\n", 0x0f);

		}
		else if ( strcmp ( cmd , "echo" ) == 0 )
		{
                        tty_printf(args[1], 0x0f);                                               tty_printf(" ", 0x0f);
			tty_printf(args[2], 0x0f);
                        tty_printf(" ", 0x0f);
                        tty_printf(args[3], 0x0f);                                               tty_printf(" ", 0x0f);
                        tty_printf(args[4], 0x0f);                                               tty_printf(" ", 0x0f);                      
                        tty_printf(args[5], 0x0f);                                               tty_printf(" ", 0x0f);                                                tty_printf(args[6], 0x0f);                                               tty_printf(" ", 0x0f);                       
                        tty_printf(args[7], 0x0f);
                        tty_printf(" ", 0x0f);
                        tty_printf(args[8], 0x0f);
                        tty_printf(" ", 0x0f);                                                tty_printf(args[9], 0x0f);                                               tty_printf(" ", 0x0f);
			tty_printf("\n", 0x0f);

		}
		else if ( strcmp ( cmd , "args" ) == 0 )
		{
			tty_printf( args[atoi(args[1])] , 0x0f );
			tty_printf ("\n", 0x0f);
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
			a = (int*)malloc(n * sizeof(int));
			for (i = 0; i<n; i++)
			{
				tty_printf("enter element of array: ", 0x0f);
				a[i] = atoi(keyboard_getstring());
			}
			tty_printf("your dynamic array: ", 0x0f);
			for (i = 0; i<n; i++) {
				tty_printf(itoa(a[i]), 0x0f);
				tty_printf(" ", 0x0f);
			}
			free(a);
			tty_printf("\nArray deleted. Memory cleaned.\n", 0x0f);
		}
		else if ( strcmp ( cmd , "panic-test" ) == 0 )
		{
			panic("test panic");
		}
		else if ( strcmp ( cmd , "reboot" ) == 0 )
		{
			reboot();
		}
   		else if ( strcmp( cmd , "malloc") == 0)
    	{
      		char * a;
			*a = (char*)malloc(sizeof(char) * atoi(args[1]));
      		for (int i = 0; i < atoi(args[1]); i++)
        		*a++ = 'q';
      		tty_printf("OK\n", 0x0f);
   		}
		else if ( strcmp ( cmd , "changelog" ) == 0 )
		{
			tty_printf("New in vtos 5.4: \ncursor\nnew directory structure\n", 0x0f);
		}
		else if ( strcmp ( cmd , "setps1" ) == 0 )
		{
			if ( strcmp ( args[1] , "setps1" ) == 0 )
			{
				tty_printf ( "PS1 cat't be blank.\n" , 0x0f );
			}
			else
			{
				strcpy ( PS1 , args[1] );
				tty_printf ( "Done.\n" , 0x0f );
			}
		}
		else if ( strcmp ( cmd , "calc" ) == 0 )
		{
			unsigned long long int c1 = atoi ( args[1] );
			unsigned long long int c2 = atoi ( args[3] );

			if ( strcmp ( args[2] , "+" ) == 0 )
			{
				tty_printf( itoa ( c1 + c2 ) , 0x0f );
				tty_printf("\n",0x0f);
			}
			else if ( strcmp ( args[2] , "-" ) == 0 )
                        {
                                tty_printf( itoa ( c1 - c2 ) , 0x0f );
                                tty_printf("\n",0x0f);
			}
			else if ( strcmp ( args[2] , "*" ) == 0 )
                        {
                                tty_printf( itoa ( c1 * c2 ) , 0x0f );
                                tty_printf("\n",0x0f);
			}
			else if ( strcmp ( args[2] , "/" ) == 0 )
                        {
				if ( strcmp ( args[3] , "0" ) == 0 )
				{
					tty_printf ( "Error: ", 0x04 );
					tty_printf ( "division by zero." ,0x0f);
				}
				else if ( strcmp ( args[3] , "/" ) == 0 )
				{
					tty_printf ( "Error: ", 0x04 );
					tty_printf ( "Illegal argument." ,0x0f);
				}
				else
				{
                                tty_printf( itoa ( c1 / c2 ) , 0x0f );
				}

                                tty_printf("\n",0x0f);
			}
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
