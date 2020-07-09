#include <memory.h>
#include <string.h>

char* s_strpbrk(char *string1, char *string2)
{
    int i, j, pos, flag = 0;
    for (i = 0; string1[i] != '\0';i++);
    pos = i;
    for (i = 0;string2[i] != '\0';i++)
    {
        for (j = 0;string1[j] != '\0';j++)
        {
            if (string2[i] == string1[j])
            {
                if (j <= pos)
                {
                    pos = j;
                    flag = 1;
                }
            }
         }
    }
    if (flag == 1)
    {
        return &string1[pos];
    }
    else
    {
        return NULL;
    }
}

char* s_strdup(char *src)
{
    char *str;
    char *p;
    int len = 0;

    while (src[len])
        len++;
    str = malloc(len + 1);
    p = str;
    while (*src)
        *p++ = *src++;
    *p = '\0';
    return str;
}

char* s_strsep(char **stringp, const char *delim) 
{
	if (*stringp == NULL) 
	{ 
		return NULL; 
	}
	char *token_start = *stringp;
	*stringp = s_strpbrk(token_start, delim);
	if (*stringp) 
	{
		**stringp = '\0';
		(*stringp)++;
	}
	return token_start;
}

char** split (const char* what , const char* deli)
{
	char *token, *str;

	char* massiv[100];

	int x = 0;

	str = s_strdup(what); 

	while ((token = s_strsep(&str, deli))) 
	{
		massiv[x++] = token;
		// printf ("%s\n" , token);
	}
	return (massiv);
}
int sptlen (const char* what , const char* deli)
{                                                                             char *token, *str;
	int x = 0;
	str = s_strdup(what);
	while ((token = s_strsep(&str, deli)))
	{ 
		x++;
		tty_printf("x++;",0x0f);
	}
	return (x);
}

