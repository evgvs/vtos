
#include <string.h>

char* str_split(char string[50], char* who , int c)
{

	int count=0;
	char* massiv[15];
	char * token = strtok(string, who);

	while ( token != NULL )
       	{
		massiv[count++] = token;
		token = strtok(NULL, who);
	}

	return massiv[c];
}

